#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>
#include <windows.h>

#define LIMPAR_TELA() system("cls")


#define MAX 100
#define MAX_DEP 10

// Estruturas para armazenar os dados das famílias
typedef struct {
    char nome[80];
    int idade;
    char rg[10];
    char cpf[12];
    char naturalidade[50];
    char profissao[50];
    char emprego[50];
} Pessoa;
// Estrutura para armazenar o endereço da família
typedef struct {
    char endereco[100];
    char numero[20];
    char bairro[50];
    char telefone[30];
} Endereco;
// Estrutura para armazenar os dados dos dependentes
typedef struct {
    char nome[80];
    int idade;
    char sexo[20];
    char parentesco[30];
} Dependente;
// Estrutura para armazenar o estado civil da família
typedef struct {
    char casadosCivil[3];
    char pretendeCasarCivil[3];
    char casadosIgreja[3];
    char pretendeCasarIgreja[3];
} EstadoCivil;
// Estrutura para armazenar as informações religiosas da família
typedef struct {
    char catolicos[4];
    char praticantes[4];
    char igreja[50];
    char semBatismo[4];
    int qntSemBatismo;
    char eucaristia[4];
    int qntEucaristia;
} Religiao;
// Estrutura para armazenar as informações financeiras da família
typedef struct {
    int qntTrabalham;
    float renda;
    char casaPropria[4];
    float aluguel;
    char pagaPrestacoes[10];
    char prestacaoDeQue[80];
    float valorPrestacao;
    char recebeAuxilio[10];
    char qualAuxilio[100];
} Financeiro;
// Estrutura para armazenar as informações de saúde da família
typedef struct {
    char haDoentes[10];
    char quemDoente[100];
    char assistenciaMedica[10];
    char ondeAssistencia[80];
} Saude;
// Estrutura para controle interno da sociedade vicentinos
typedef struct {
    char necessitaAdotada[10];
    char ateQuando[50];
    char admitidaEm[20];
    char excluidaEm[20];
    char promovida[10];
    char sindicanciaPor[100];
    char dataSindicancia[20];
    char observacoes[200];
} Controle;
// Estrutura principal para armazenar os dados de cada família
typedef struct {
    int ficha;
    char conferencia[50];
    Pessoa atendido;
    char possuiCompanheiro[10];
    Pessoa esposo;
    Endereco endereco;
    EstadoCivil estadoCivil;
    int qtdDependentes;
    Dependente dependentes[MAX_DEP];
    Religiao religiao;
    Financeiro financeiro;
    Saude saude;
    Controle controle;
} Familia;
// Variáveis globais para armazenar as famílias, o total de famílias cadastradas e a próxima ficha a ser gerada
Familia familias[MAX];
int total = 0;
int proximaFicha = 1;
// Protótipos das funções
// Função para limpar o buffer do teclado, usada para evitar problemas com fgets e scanf
void limparBuffer()
{
    int c;
    while((c = getchar()) != '\n' && c != EOF) {}
}

void pausar()
{
    printf("\nPressione ENTER para continuar...");
    limparBuffer();
    getchar();
}
// Função para verificar se o usuário digitou "CANCELAR"
int cancelouTexto(char texto[])
{
    return strcmp(texto, "CANCELAR") == 0 ||
           strcmp(texto, "cancelar") == 0 ||
           strcmp(texto, "Cancelar") == 0;
}
// Função para validar se o texto contém apenas números
int somenteNumeros(char texto[])
{
    int i;
    if(strlen(texto) == 0) return 0;

    for(i = 0; texto[i] != '\0'; i++)
    {
        if(texto[i] < '0' || texto[i] > '9')
            return 0;
    }
    return 1;
}
// Função para validar se o texto contém apenas letras e espaços

int somenteLetras(char texto[])
{
    int i;
    if(strlen(texto) == 0) return 0;

    for(i = 0; texto[i] != '\0'; i++)
    {
        unsigned char c = (unsigned char)texto[i];

        if(!isalpha(c) && c != ' ' && c < 0x80)
            return 0;
    }
    return 1;
}
// Função para validar se o texto contém apenas letras, números, espaços e alguns caracteres de pontuação

int letrasNumerosEspaco(char texto[])
{
    int i;
    if(strlen(texto) == 0) return 0;

    for(i = 0; texto[i] != '\0'; i++)
    {
        unsigned char c = (unsigned char)texto[i];

        if(!isalnum(c) && c != ' ' && c != '.' && c != ',' && c != '-' && c < 0x80)
            return 0;
    }
    return 1;
}
// Função para ler um nome com validação e opção de cancelar
int lerNome(char nome[], char mensagem[])
{
    do
    {
        printf("%s", mensagem);
        scanf(" %79[^\n]", nome);

        if(cancelouTexto(nome)) return 0;

        if(somenteLetras(nome) == 0)
            printf("Entrada invalida. Digite apenas letras.\n");

    } while(somenteLetras(nome) == 0);

    return 1;
}
// Função para ler um texto com validação de letras, números e espaços, e opção de cancelar
int lerTextoValidado(char texto[], int tamanho, char mensagem[])
{
    do
    {
        printf("%s", mensagem);

        if(tamanho == 20)
            scanf(" %19[^\n]", texto);
        else if(tamanho == 50)
            scanf(" %49[^\n]", texto);
        else if(tamanho == 80)
            scanf(" %79[^\n]", texto);
        else if(tamanho == 100)
            scanf(" %99[^\n]", texto);
        else if(tamanho == 200)
            scanf(" %199[^\n]", texto);
        else
            scanf(" %99[^\n]", texto);

        if(cancelouTexto(texto)) return 0;

        if(letrasNumerosEspaco(texto) == 0)
            printf("Entrada invalida. Digite letras, numeros ou espacos.\n");

    } while(letrasNumerosEspaco(texto) == 0);

    return 1;
}
// Função para ler um endereço com validação e opção de cancelar
int lerEndereco(char texto[], char mensagem[])
{
    return lerTextoValidado(texto, 100, mensagem);
}
// Função para ler o número da casa com validação de apenas números e opção de cancelar
int lerNumeroCasa(char numero[])
{
    do
    {
        printf("Número: ");
        scanf(" %19[^\n]", numero);

        if(cancelouTexto(numero)) return 0;

        if(somenteNumeros(numero) == 0)
            printf("Número inválido. Digite apenas números.\n");

    } while(somenteNumeros(numero) == 0);

    return 1;
}
// Função para ler uma opção de menu (número inteiro), sem opção de cancelar.
int lerOpcaoMenu(int minimo, int maximo)
{
    char texto[30];
    int valor;

    do
    {
        scanf(" %29[^\n]", texto);

        if(somenteNumeros(texto) == 0)
        {
            printf("Entrada inválida. Digite apenas números.\n");
            printf("Opção: ");
            continue;
        }

        valor = atoi(texto);

        if(valor < minimo || valor > maximo)
        {
            printf("Opção inválida. Tente novamente!\n");
            printf("Opção: ");
            continue;
        }

        return valor;

    } while(1);
}
// Função para ler um inteiro com validação de apenas números, limite mínimo e máximo, e opção de cancelar
int lerInteiro(int *numero, char mensagem[], int minimo, int maximo)
{
    char texto[30];

    do
    {
        printf("%s", mensagem);
        scanf(" %29[^\n]", texto);

        if(cancelouTexto(texto)) return 0;

        if(somenteNumeros(texto) == 0)
        {
            printf("Entrada inválida. Digite apenas números.\n");
        }
        else
        {
            *numero = atoi(texto);

            if(*numero < minimo || *numero > maximo)
                printf("Valor inválido. Digite um número entre %d e %d.\n", minimo, maximo);
            else
                return 1;
        }

    } while(1);
}
// Função para ler um número float com validação de apenas números, um ponto decimal, e opção de cancelar
int lerFloat(float *numero, char mensagem[])
{
    char texto[30];
    int i, pontos;

    do
    {
        pontos = 0;
        printf("%s", mensagem);
        scanf(" %29[^\n]", texto);

        if(cancelouTexto(texto)) return 0;

        for(i = 0; texto[i] != '\0'; i++)
        {
            if(texto[i] == ',') texto[i] = '.';
        }

        for(i = 0; texto[i] != '\0'; i++)
        {
            if(texto[i] == '.')
                pontos++;
            else if(texto[i] < '0' || texto[i] > '9')
                pontos = 99;
        }

        if(pontos > 1)
            printf("Valor inválido. Digite apenas números. Exemplo: 1250.50 .\n");
        else
        {
            *numero = atof(texto);
            return 1;
        }

    } while(1);
}
// Função para ler um CPF com validação de apenas números, 11 dígitos, e opção de cancelar
int lerCPF(char cpf[])
{
    do
    {
        printf("CPF: ");
        scanf(" %11[^\n]", cpf);

        if(cancelouTexto(cpf)) return 0;

        if(strlen(cpf) != 11 || somenteNumeros(cpf) == 0)
            printf("CPF inválido. Digite apenas 11 números.\n");

    } while(strlen(cpf) != 11 || somenteNumeros(cpf) == 0);

    return 1;
}
// Função para ler um RG com validação de apenas números, 9 dígitos, e opção de cancelar
int lerRG(char rg[])
{
    do
    {
        printf("RG: ");
        scanf(" %9[^\n]", rg);

        if(cancelouTexto(rg)) return 0;

        if(strlen(rg) != 9 || somenteNumeros(rg) == 0)
            printf("RG inválido. Digite apenas 9 números.\n");

    } while(strlen(rg) != 9 || somenteNumeros(rg) == 0);

    return 1;
}
// Função para ler um telefone com validação de apenas números, 10 ou 11 dígitos, e opção de cancelar
int lerTelefone(char telefone[])
{
    do
    {
        printf("Telefone: ");
        scanf(" %12[^\n]", telefone);

        if(cancelouTexto(telefone)) return 0;

        if((strlen(telefone) != 10 && strlen(telefone) != 11) || somenteNumeros(telefone) == 0)
            printf("Telefone inválido. Digite apenas 10 ou 11 números.\n");

    } while((strlen(telefone) != 10 && strlen(telefone) != 11) || somenteNumeros(telefone) == 0);

    return 1;
}
// Função para ler uma resposta de sim ou não com validação e opção de cancelar
int lerSimNao(char resposta[], char mensagem[])
{
    do
    {
        printf("%s", mensagem);
        scanf(" %9s", resposta);

        if(strcmp(resposta, "sim") == 0 || strcmp(resposta, "SIM") == 0 || strcmp(resposta, "Sim") == 0 || strcmp(resposta, "s") == 0 || strcmp(resposta, "S") == 0)
        {
            strcpy(resposta, "sim");
            return 1;
        }
        else if(strcmp(resposta, "não") == 0 || strcmp(resposta, "NÃO") == 0 || strcmp(resposta, "Não") == 0 || strcmp(resposta, "n") == 0 || strcmp(resposta, "N") == 0 || strcmp(resposta, "nao") == 0)
        {
            strcpy(resposta, "não");
            return 1;
        }
        else if(strcmp(resposta, "cancelar") == 0 ||
        strcmp(resposta, "CANCELAR") == 0 ||
        strcmp(resposta, "Cancelar") == 0)
        {
            return 0;
        }
        else
        {
            printf("Resposta inválida. Digite sim ou não .\n");
        }

    } while(1);
}
// Função para ler o sexo com validação de apenas 'F' ou 'M', e opção de cancelar
int lerSexo(char sexo[], char mensagem[])
{
    do
    {
        printf("%s", mensagem);
        scanf(" %19s", sexo);

        if(strcmp(sexo, "F") == 0 || strcmp(sexo, "f") == 0)
        {
            strcpy(sexo, "F");
            return 1;
        }
        else if(strcmp(sexo, "M") == 0 || strcmp(sexo, "m") == 0)
        {
            strcpy(sexo, "M");
            return 1;
        }
        else if(strcmp(sexo, "cancelar") == 0 ||
        strcmp(sexo, "CANCELAR") == 0 ||
        strcmp(sexo, "Cancelar") == 0)
        {
            return 0;
        }
        else
        {
            printf("Sexo inválido. Digite F ou M .\n");
        }

    } while(1);
}
// Função para verificar se um CPF já está cadastrado, ignorando a posição atual para evitar duplicação na edição
int cpfJaCadastrado(char cpf[], int cadastroAtual)
{
    int i;
    for(i = 0; i < total; i++)
    {
        if(i != cadastroAtual && strcmp(familias[i].atendido.cpf, cpf) == 0)
            return 1;
    }
    return 0;
}
// Função para verificar se um RG já está cadastrado, ignorando a posição atual para evitar duplicação na edição
int rgJaCadastrado(char rg[], int cadastroAtual)
{
    int i;
    for(i = 0; i < total; i++)
    {
        if(i != cadastroAtual && strcmp(familias[i].atendido.rg, rg) == 0)
            return 1;
    }
    return 0;
}
// Função para limpar os dados de uma pessoa, usada para limpar os dados do companheiro(a) quando não houver
void limparPessoa(Pessoa *p)
{
    strcpy(p->nome, "-");
    p->idade = 0;
    strcpy(p->rg, "-");
    strcpy(p->cpf, "-");
    strcpy(p->naturalidade, "-");
    strcpy(p->profissao, "-");
    strcpy(p->emprego, "-");
}
// Função para salvar os dados das famílias em um arquivo de texto formatado
void salvarDadosTxt()
{
    FILE *arquivo = fopen("familias.txt", "w");

    int i, j;

    if(arquivo == NULL)
    {
        printf("Erro ao salvar o arquivo familias.txt.\n");
        return;
    }

    fprintf(arquivo, "----------------------------------------------\n");
    fprintf(arquivo, "       SISTEMA VICENTINOS - SANTA CRUZ\n");
    fprintf(arquivo, "----------------------------------------------\n");
    fprintf(arquivo, "Total de famílias ativas: %d\n", total);
    fprintf(arquivo, "Total de fichas geradas no projeto: %d\n", proximaFicha - 1);
    fprintf(arquivo, "Próxima ficha: %d\n\n", proximaFicha);

    if(total == 0)

        fprintf(arquivo, "Nenhuma família cadastrada.\n");

    for(i = 0; i < total; i++)
    {
        fprintf(arquivo, "---------------------------------------------\n");
        fprintf(arquivo, "FICHA: %d\n", familias[i].ficha);
        fprintf(arquivo, "CONFERENCIA: %s\n", familias[i].conferencia);
        fprintf(arquivo, "---------------------------------------------\n");

        fprintf(arquivo, "\n--- DADOS DO ATENDIDO(A) ---\n");
        fprintf(arquivo, "Nome: %s\n", familias[i].atendido.nome);
        fprintf(arquivo, "Idade: %d\n", familias[i].atendido.idade);
        fprintf(arquivo, "RG: %s\n", familias[i].atendido.rg);
        fprintf(arquivo, "CPF: %s\n", familias[i].atendido.cpf);
        fprintf(arquivo, "Naturalidade: %s\n", familias[i].atendido.naturalidade);
        fprintf(arquivo, "Profissão: %s\n", familias[i].atendido.profissao);
        fprintf(arquivo, "Emprego: %s\n", familias[i].atendido.emprego);

        fprintf(arquivo, "\n--- ENDEREÇO ---\n");
        fprintf(arquivo, "Endereço: %s, número %s\n", familias[i].endereco.endereco, familias[i].endereco.numero);
        fprintf(arquivo, "Bairro: %s\n", familias[i].endereco.bairro);
        fprintf(arquivo, "Telefone: %s\n", familias[i].endereco.telefone);

        fprintf(arquivo, "\n--- COMPANHEIRO(A) ---\n");
        fprintf(arquivo, "Possui companheiro(a): %s\n", familias[i].possuiCompanheiro);
        fprintf(arquivo, "Nome: %s\n", familias[i].esposo.nome);
        fprintf(arquivo, "Idade: %d\n", familias[i].esposo.idade);
        fprintf(arquivo, "RG: %s\n", familias[i].esposo.rg);
        fprintf(arquivo, "CPF: %s\n", familias[i].esposo.cpf);
        fprintf(arquivo, "Naturalidade: %s\n", familias[i].esposo.naturalidade);
        fprintf(arquivo, "Profissão: %s\n", familias[i].esposo.profissao);
        fprintf(arquivo, "Emprego: %s\n", familias[i].esposo.emprego);

        fprintf(arquivo, "\n--- ESTADO CIVIL ---\n");
        fprintf(arquivo, "Casados no civil: %s\n", familias[i].estadoCivil.casadosCivil);
        fprintf(arquivo, "Pretende casar no civil: %s\n", familias[i].estadoCivil.pretendeCasarCivil);
        fprintf(arquivo, "Casados na igreja: %s\n", familias[i].estadoCivil.casadosIgreja);
        fprintf(arquivo, "Pretende casar na igreja: %s\n", familias[i].estadoCivil.pretendeCasarIgreja);

        fprintf(arquivo, "\n--- DEPENDENTES ---\n");
        fprintf(arquivo, "Quantidade de dependentes: %d\n", familias[i].qtdDependentes);

        for(j = 0; j < familias[i].qtdDependentes; j++)
        {
            fprintf(arquivo, "Dependente %d\n", j + 1);
            fprintf(arquivo, "Nome: %s\n", familias[i].dependentes[j].nome);
            fprintf(arquivo, "Idade: %d\n", familias[i].dependentes[j].idade);
            fprintf(arquivo, "Sexo: %s\n", familias[i].dependentes[j].sexo);
            fprintf(arquivo, "Parentesco: %s\n", familias[i].dependentes[j].parentesco);
        }

        fprintf(arquivo, "\n--- INFORMAÇÕES RELIGIOSAS ---\n");
        fprintf(arquivo, "Católicos: %s\n", familias[i].religiao.catolicos);
        fprintf(arquivo, "Praticantes: %s\n", familias[i].religiao.praticantes);
        fprintf(arquivo, "Igreja: %s\n", familias[i].religiao.igreja);
        fprintf(arquivo, "Alguém sem batismo: %s\n", familias[i].religiao.semBatismo);
        fprintf(arquivo, "Quantidade sem batismo: %d\n", familias[i].religiao.qntSemBatismo);
        fprintf(arquivo, "Alguém para fazer a 1 Eucaristia: %s\n", familias[i].religiao.eucaristia);
        fprintf(arquivo, "Quantidade para Eucaristia: %d\n", familias[i].religiao.qntEucaristia);

        fprintf(arquivo, "\n--- INFORMAÇÕES FINANCEIRAS ---\n");
        fprintf(arquivo, "Quantos trabalham: %d\n", familias[i].financeiro.qntTrabalham);
        fprintf(arquivo, "Renda familiar: R$ %.2f\n", familias[i].financeiro.renda);
        fprintf(arquivo, "Casa própria: %s\n", familias[i].financeiro.casaPropria);
        fprintf(arquivo, "Aluguel: R$ %.2f\n", familias[i].financeiro.aluguel);
        fprintf(arquivo, "Paga prestações: %s\n", familias[i].financeiro.pagaPrestacoes);
        fprintf(arquivo, "Prestação de que: %s\n", familias[i].financeiro.prestacaoDeQue);
        fprintf(arquivo, "Valor da prestação: R$ %.2f\n", familias[i].financeiro.valorPrestacao);
        fprintf(arquivo, "Recebe auxílio: %s\n", familias[i].financeiro.recebeAuxilio);
        fprintf(arquivo, "Qual auxílio: %s\n", familias[i].financeiro.qualAuxilio);

        fprintf(arquivo, "\n--- SAÚDE ---\n");
        fprintf(arquivo, "Há doentes na família? %s\n", familias[i].saude.haDoentes);
        fprintf(arquivo, "Quem está doente? %s\n", familias[i].saude.quemDoente);
        fprintf(arquivo, "Tem assistência médica? %s\n", familias[i].saude.assistenciaMedica);
        fprintf(arquivo, "Onde? %s\n", familias[i].saude.ondeAssistencia);

        fprintf(arquivo, "\n--- CONTROLE DA SOCIEDADE ---\n");
        fprintf(arquivo, "Necessita ser adotada: %s\n", familias[i].controle.necessitaAdotada);
        fprintf(arquivo, "Até quando: %s\n", familias[i].controle.ateQuando);
        fprintf(arquivo, "Admitida em: %s\n", familias[i].controle.admitidaEm);
        fprintf(arquivo, "Excluída em: %s\n", familias[i].controle.excluidaEm);
        fprintf(arquivo, "Foi promovida: %s\n", familias[i].controle.promovida);
        fprintf(arquivo, "Sindicância feita por: %s\n", familias[i].controle.sindicanciaPor);
        fprintf(arquivo, "Data da sindicância: %s\n", familias[i].controle.dataSindicancia);
        fprintf(arquivo, "Observações: %s\n\n", familias[i].controle.observacoes);
    }

    fclose(arquivo);
}
// Função para salvar os dados das famílias em um arquivo binário e também em um arquivo de texto formatado
void salvarDados()
{
    FILE *arquivo = fopen("familias.dat", "wb");

    if(arquivo != NULL)
    {
        fwrite(&total, sizeof(int), 1, arquivo);
        fwrite(&proximaFicha, sizeof(int), 1, arquivo);
        fwrite(familias, sizeof(Familia), MAX, arquivo);
        fclose(arquivo);
        salvarDadosTxt();
    }
    else
    {
        printf("Erro ao salvar os dados no arquivo familias.dat.\n");
    }
}
// Função para carregar os dados das famílias de um arquivo binário
void carregarDados()
{
    FILE *arquivo = fopen("familias.dat", "rb");

    if(arquivo != NULL)
    {
        fread(&total, sizeof(int), 1, arquivo);
        fread(&proximaFicha, sizeof(int), 1, arquivo);
        fread(familias, sizeof(Familia), MAX, arquivo);
        fclose(arquivo);
    }
}
// Função para cadastrar ou editar uma família, com validação e opção de cancelar
int cadastrarFamilia(int pos)
{
    int i;

        printf("\n---------------------------------------------\n");
        printf("                ATENÇÃO\n");
        printf("   Digite CANCELAR a qualquer momento\n");
        printf("   para interromper o cadastro.\n");
        printf("---------------------------------------------\n\n");
    if(pos == total)
    {
        familias[pos].ficha = proximaFicha;
        proximaFicha++;
    }

    strcpy(familias[pos].conferencia, "Santa Cruz");

    printf("Ficha: %d\n", familias[pos].ficha);

    printf("\n--- DADOS ---\n\n");

    if(lerNome(familias[pos].atendido.nome, "Nome do atendido(a): ") == 0) return 0;
    if(lerInteiro(&familias[pos].atendido.idade, "Idade: ", 0, 120) == 0) return 0;

    do
    {
        if(lerRG(familias[pos].atendido.rg) == 0) return 0;
        if(rgJaCadastrado(familias[pos].atendido.rg, pos))
            printf("RG já cadastrado. Digite outro RG.\n");
    } while(rgJaCadastrado(familias[pos].atendido.rg, pos));

    do
    {
        if(lerCPF(familias[pos].atendido.cpf) == 0) return 0;
        if(cpfJaCadastrado(familias[pos].atendido.cpf, pos))
            printf("CPF já cadastrado. Digite outro CPF.\n");
    } while(cpfJaCadastrado(familias[pos].atendido.cpf, pos));

    if(lerNome(familias[pos].atendido.naturalidade, "Naturalidade: ") == 0) return 0;
    if(lerNome(familias[pos].atendido.profissao, "Profissão: ") == 0) return 0;
    if(lerTextoValidado(familias[pos].atendido.emprego, 50, "Emprego: ") == 0) return 0;

    printf("\n\n--- ENDEREÇO ---\n\n");

    if(lerEndereco(familias[pos].endereco.endereco, "Endereço: ") == 0) return 0;
    if(lerNumeroCasa(familias[pos].endereco.numero) == 0) return 0;
    if(lerNome(familias[pos].endereco.bairro, "Bairro: ") == 0) return 0;
    if(lerTelefone(familias[pos].endereco.telefone) == 0) return 0;

    printf("\n\n--- COMPANHEIRO(A) ---\n\n");

    if(lerSimNao(familias[pos].possuiCompanheiro, "Possui companheiro(a)? Digite sim ou não: ") == 0) return 0;

    if(familias[pos].possuiCompanheiro[0] == 's')
    {
        if(lerNome(familias[pos].esposo.nome, "Nome do esposo(a): ") == 0) return 0;
        if(lerInteiro(&familias[pos].esposo.idade, "Idade do esposo(a): ", 0, 120) == 0) return 0;
        if(lerRG(familias[pos].esposo.rg) == 0) return 0;
        if(lerCPF(familias[pos].esposo.cpf) == 0) return 0;
        if(lerNome(familias[pos].esposo.naturalidade, "Naturalidade do esposo(a): ") == 0) return 0;
        if(lerNome(familias[pos].esposo.profissao, "Profissão do esposo(a): ") == 0) return 0;
        if(lerTextoValidado(familias[pos].esposo.emprego, 50, "Emprego do esposo(a): ") == 0) return 0;
    }
    else
    {
        limparPessoa(&familias[pos].esposo);
    }

    if(familias[pos].possuiCompanheiro[0] == 's')
{
        printf("\n\n--- Estado civil ---\n");//alterado seguimento das perguntas(Paty)

    if(lerSimNao(familias[pos].estadoCivil.casadosCivil,"Casados no civil? ") == 0)
        return 0;

    if(familias[pos].estadoCivil.casadosCivil[0] == 'n')
    {
    if(lerSimNao(familias[pos].estadoCivil.pretendeCasarCivil,"Pretende casar no civil? ") == 0)
            return 0;
    }
    else
    {
        strcpy(familias[pos].estadoCivil.pretendeCasarCivil,"-");
    }

    if(lerSimNao(familias[pos].estadoCivil.casadosIgreja,"Casados na igreja? ") == 0)
            return 0;

    if(familias[pos].estadoCivil.casadosIgreja[0] == 'n')
    {
        if(lerSimNao(familias[pos].estadoCivil.pretendeCasarIgreja,"Pretende casar na igreja? ") == 0)
            return 0;
    }
    else
    {
        strcpy(familias[pos].estadoCivil.pretendeCasarIgreja,"-");
    }
}
    else
{
    strcpy(familias[pos].estadoCivil.casadosCivil, "-");
    strcpy(familias[pos].estadoCivil.pretendeCasarCivil, "-");
    strcpy(familias[pos].estadoCivil.casadosIgreja, "-");
    strcpy(familias[pos].estadoCivil.pretendeCasarIgreja, "-");
}

    printf("\n\n--- DEPENDENTES ---\n\n");

    if(lerInteiro(&familias[pos].qtdDependentes,"Quantidade de dependentes: ",0,MAX_DEP) == 0)
    return 0;

    for(i = 0; i < familias[pos].qtdDependentes; i++)
{
    printf("\nDependente %d\n", i + 1);

    if(lerNome(familias[pos].dependentes[i].nome,"Nome: ") == 0)
    return 0;

    if(lerInteiro(&familias[pos].dependentes[i].idade,"Idade: ",0,120) == 0)
        return 0;

    if(lerSexo(familias[pos].dependentes[i].sexo,"Sexo (F/M): ") == 0)
    return 0;

    if(lerNome(familias[pos].dependentes[i].parentesco,"Parentesco: ") == 0)
    return 0;
}


    printf("\n\n--- INFORMAÇÕES RELIGIOSAS ---\n\n");

    if(lerSimNao(familias[pos].religiao.catolicos, "São católicos? Digite sim ou não: ") == 0) return 0;

    if(familias[pos].religiao.catolicos[0] == 's')
    {
        if(lerSimNao(familias[pos].religiao.praticantes, "São praticantes? Digite sim ou não: ") == 0) return 0;

    if(familias[pos].religiao.praticantes[0] == 's')
    {
        if(lerNome(familias[pos].religiao.igreja,"Igreja: ") == 0)
            return 0;
    }
    else
    {
        strcpy(familias[pos].religiao.igreja, "-");
    }

    if(lerSimNao(familias[pos].religiao.semBatismo, "Alguém sem batismo? Digite sim ou não: ") == 0) return 0;
    if(familias[pos].religiao.semBatismo[0] == 's')
    {
        if(lerInteiro(&familias[pos].religiao.qntSemBatismo,"Quantos sem batismo? ",1,50) == 0)
            return 0;
    }
    else
    {
        familias[pos].religiao.qntSemBatismo = 0;
    }

    if(lerSimNao(familias[pos].religiao.eucaristia,"Alguém para fazer a 1 Eucaristia? ") == 0)
        return 0;

    if(familias[pos].religiao.eucaristia[0] == 's')
    {
        if(lerInteiro(&familias[pos].religiao.qntEucaristia,"Quantos para Eucaristia? ",1,50) == 0)
            return 0;
    }
    else
    {
        familias[pos].religiao.qntEucaristia = 0;
    }
}
    else
{
        strcpy(familias[pos].religiao.praticantes, "-");
        strcpy(familias[pos].religiao.igreja, "-");
        strcpy(familias[pos].religiao.semBatismo, "-");
        strcpy(familias[pos].religiao.eucaristia, "-");

        familias[pos].religiao.qntSemBatismo = 0;
        familias[pos].religiao.qntEucaristia = 0;
}
    printf("\n\n--- INFORMAÇÕES FINANCEIRAS ---\n\n");

    if(lerInteiro(&familias[pos].financeiro.qntTrabalham, "Quantos trabalham? ", 0, 50) == 0) return 0;
    if(lerFloat(&familias[pos].financeiro.renda, "Renda familiar: R$ ") == 0) return 0;

    if(lerSimNao(familias[pos].financeiro.casaPropria, "A casa é própria? Digite sim ou não: ") == 0) return 0;
    if(familias[pos].financeiro.casaPropria[0] == 'n')
    {
        if(lerFloat(&familias[pos].financeiro.aluguel, "Quanto paga de aluguel? R$ ") == 0) return 0;
    }
    else
    {
        familias[pos].financeiro.aluguel = 0;
    }

    if(lerSimNao(familias[pos].financeiro.pagaPrestacoes, "Paga prestacoes? Digite sim ou não: ") == 0) return 0;
    if(familias[pos].financeiro.pagaPrestacoes[0] == 's')
    {
        if(lerTextoValidado(familias[pos].financeiro.prestacaoDeQue, 80, "Prestacao de que? ") == 0) return 0;
        if(lerFloat(&familias[pos].financeiro.valorPrestacao, "Valor da prestacao: R$ ") == 0) return 0;
    }
    else
    {
        strcpy(familias[pos].financeiro.prestacaoDeQue, "-");
        familias[pos].financeiro.valorPrestacao = 0;
    }

    if(lerSimNao(familias[pos].financeiro.recebeAuxilio, "Recebe algum auxílio? Digite sim ou não: ") == 0) return 0;
    if(familias[pos].financeiro.recebeAuxilio[0] == 's')
    {
        if(lerTextoValidado(familias[pos].financeiro.qualAuxilio, 100, "Qual auxílio? ") == 0) return 0;
    }
    else
    {
        strcpy(familias[pos].financeiro.qualAuxilio, "-");
    }

    printf("\n\n--- SAÚDE ---\n\n");

    if(lerSimNao(familias[pos].saude.haDoentes, "Há doentes na família? Digite sim ou não: ") == 0) return 0;
    if(familias[pos].saude.haDoentes[0] == 's')
    {
        if(lerTextoValidado(familias[pos].saude.quemDoente, 100, "Quem está doente? ") == 0) return 0;
    }
    else
    {
        strcpy(familias[pos].saude.quemDoente, "-");
    }

    if(lerSimNao(familias[pos].saude.assistenciaMedica, "Tem assistência médica? Digite sim ou não: ") == 0) return 0;
    if(familias[pos].saude.assistenciaMedica[0] == 's')
    {
        if(lerTextoValidado(familias[pos].saude.ondeAssistencia, 80, "Onde? ") == 0) return 0;
    }
    else
    {
        strcpy(familias[pos].saude.ondeAssistencia, "-");
    }

    printf("\n\n--- CONTROLE DA SOCIEDADE ---\n\n");

    if(lerSimNao(familias[pos].controle.necessitaAdotada, "Necessita ser adotada? Digite sim ou não: ") == 0) return 0;
    if(familias[pos].controle.necessitaAdotada[0] == 's')
    {
        if(lerTextoValidado(familias[pos].controle.ateQuando, 50, "Até quando? ") == 0) return 0;
    }
    else
    {
        strcpy(familias[pos].controle.ateQuando, "-");
    }

    if(lerTextoValidado(familias[pos].controle.admitidaEm, 20, "Admitida em: ") == 0)
        return 0;
    if(lerTextoValidado(familias[pos].controle.excluidaEm, 20, "Excluida em: ") == 0)
        return 0;
    if(lerSimNao(familias[pos].controle.promovida, "Foi promovida? Digite sim ou não: ") == 0)
        return 0;
    if(lerNome(familias[pos].controle.sindicanciaPor, "Sindicância feita por: ") == 0)
        return 0;
    {
        int dia, mes, ano;

    if(lerInteiro(&dia,"Dia da sindicância: ",1,31) == 0)
        return 0;

    if(lerInteiro(&mes,"Mês da sindicância: ",1,12) == 0)
        return 0;

    if(lerInteiro(&ano,"Ano da sindicância: ",1900,2100) == 0)
        return 0;

    sprintf(familias[pos].controle.dataSindicancia,"%02d/%02d/%04d",dia,mes,ano);
}
    {
        char possuiObs[10];

    if(lerSimNao(possuiObs,"Existe alguma observação? ") == 0)
        return 0;

    if(possuiObs[0] == 's')
    {
        if(lerTextoValidado(familias[pos].controle.observacoes,200,"Observação: ") == 0)
            return 0;
    }
    else
    {
        strcpy(familias[pos].controle.observacoes,"-");
    }
}

        return 1;
}
// Função para mostrar os dados de uma família, com validação de posição e mensagem caso a família não exista
void mostrarFamilia(int pos)
{
    int i;

    printf("\n--------------------------------------------\n");
    printf("           DADOS DA FAMILIA\n");
    printf("----------------------------------------------\n");

    printf("Ficha: %d\n", familias[pos].ficha);
    printf("Conferência: %s\n", familias[pos].conferencia);

    printf("\n\n--- ATENDIDO(A) ---\n\n");
    printf("Nome: %s\n", familias[pos].atendido.nome);
    printf("Idade: %d\n", familias[pos].atendido.idade);
    printf("RG: %s\n", familias[pos].atendido.rg);
    printf("CPF: %s\n", familias[pos].atendido.cpf);
    printf("Naturalidade: %s\n", familias[pos].atendido.naturalidade);
    printf("Profissão: %s\n", familias[pos].atendido.profissao);
    printf("Emprego: %s\n", familias[pos].atendido.emprego);

    printf("\n\n--- ENDEREÇO ---\n\n");
    printf("Endereço: %s, número %s\n", familias[pos].endereco.endereco, familias[pos].endereco.numero);
    printf("Bairro: %s\n", familias[pos].endereco.bairro);
    printf("Telefone: %s\n", familias[pos].endereco.telefone);

    printf("\n\n--- COMPANHEIRO(A) ---\n\n");
    printf("Possui companheiro(a): %s\n", familias[pos].possuiCompanheiro);
    printf("Nome: %s\n", familias[pos].esposo.nome);
    printf("Idade: %d\n", familias[pos].esposo.idade);
    printf("RG: %s\n", familias[pos].esposo.rg);
    printf("CPF: %s\n", familias[pos].esposo.cpf);
    printf("Naturalidade: %s\n", familias[pos].esposo.naturalidade);
    printf("Profissão: %s\n", familias[pos].esposo.profissao);
    printf("Emprego: %s\n", familias[pos].esposo.emprego);

    printf("\n\n--- ESTADO CIVIL ---\n\n");
    printf("Casados no civil: %s\n", familias[pos].estadoCivil.casadosCivil);
    printf("Pretende casar no civil: %s\n", familias[pos].estadoCivil.pretendeCasarCivil);
    printf("Casados na igreja: %s\n", familias[pos].estadoCivil.casadosIgreja);
    printf("Pretende casar na igreja: %s\n", familias[pos].estadoCivil.pretendeCasarIgreja);

    printf("\n\n--- DEPENDENTES ---\n\n");
    if(familias[pos].qtdDependentes == 0)
        printf("Nenhum dependente cadastrado.\n");

    for(i = 0; i < familias[pos].qtdDependentes; i++)
    {
        printf("Dependente %d: %s | Idade: %d | Sexo: %s | Parentesco: %s\n",
               i + 1,
               familias[pos].dependentes[i].nome,
               familias[pos].dependentes[i].idade,
               familias[pos].dependentes[i].sexo,
               familias[pos].dependentes[i].parentesco);
    }

    printf("\n\n--- RELIGIÃO ---\n\n");
    printf("Católicos: %s\n", familias[pos].religiao.catolicos);
    printf("Praticantes: %s\n", familias[pos].religiao.praticantes);
    printf("Igreja: %s\n", familias[pos].religiao.igreja);
    printf("Sem batismo: %s\n", familias[pos].religiao.semBatismo);
    printf("Quantidade sem batismo: %d\n", familias[pos].religiao.qntSemBatismo);
    printf("Primeira Eucaristia: %s\n", familias[pos].religiao.eucaristia);
    printf("Quantidade para Eucaristia: %d\n", familias[pos].religiao.qntEucaristia);

    printf("\n\n--- FINANCEIRO ---\n\n");
    printf("Quantos trabalham: %d\n", familias[pos].financeiro.qntTrabalham);
    printf("Renda familiar: R$ %.2f\n", familias[pos].financeiro.renda);
    printf("Casa própria: %s\n", familias[pos].financeiro.casaPropria);
    printf("Aluguel: R$ %.2f\n", familias[pos].financeiro.aluguel);
    printf("Paga prestações: %s\n", familias[pos].financeiro.pagaPrestacoes);
    printf("Prestação de que: %s\n", familias[pos].financeiro.prestacaoDeQue);
    printf("Valor da prestação: R$ %.2f\n", familias[pos].financeiro.valorPrestacao);
    printf("Recebe auxílio: %s\n", familias[pos].financeiro.recebeAuxilio);
    printf("Qual auxílio: %s\n", familias[pos].financeiro.qualAuxilio);

    printf("\n\n--- SAÚDE ---\n\n");
    printf("Há doentes: %s\n", familias[pos].saude.haDoentes);
    printf("Quem: %s\n", familias[pos].saude.quemDoente);
    printf("Assistência médica: %s\n", familias[pos].saude.assistenciaMedica);
    printf("Onde: %s\n", familias[pos].saude.ondeAssistencia);

    printf("\n\n--- CONTROLE ---\n\n");
    printf("Necessita ser adotada: %s\n", familias[pos].controle.necessitaAdotada);
    printf("Ate quando: %s\n", familias[pos].controle.ateQuando);
    printf("Admitida em: %s\n", familias[pos].controle.admitidaEm);
    printf("Excluída em: %s\n", familias[pos].controle.excluidaEm);
    printf("Foi promovida: %s\n", familias[pos].controle.promovida);
    printf("Sindicância feita por: %s\n", familias[pos].controle.sindicanciaPor);
    printf("Data da sindicância: %s\n", familias[pos].controle.dataSindicancia);
    printf("Observações: %s\n", familias[pos].controle.observacoes);
}
// Função para buscar uma família por CPF, com validação de busca e mensagem caso a família não exista
int buscarPorCPF(char busca[])
{
    int i;
    for(i = 0; i < total; i++)
    {
        if(strcmp(familias[i].atendido.cpf, busca) == 0)
            return i;
    }
    return -1;
}
// Função para comparar duas strings ignorando diferenças entre maiúsculas e minúsculas, usada na busca por nome.
int contemSemDiferenciarCaixa(char texto[], char busca[])
{
    char textoCopia[200], buscaCopia[200];
    int i;

    for(i = 0; texto[i] != '\0' && i < 199; i++)
        textoCopia[i] = (char)tolower((unsigned char)texto[i]);
    textoCopia[i] = '\0';

    for(i = 0; busca[i] != '\0' && i < 199; i++)
        buscaCopia[i] = (char)tolower((unsigned char)busca[i]);
    buscaCopia[i] = '\0';

    return strstr(textoCopia, buscaCopia) != NULL;
}
// Função para listar as famílias que possuem um nome específico, usando strstr para permitir buscas parciais, e contando o número de famílias encontradas
int listarFamiliasPorNome(char busca[])
{
    int i;
    int encontrados = 0;

    for(i = 0; i < total; i++)
    {
        if(contemSemDiferenciarCaixa(familias[i].atendido.nome, busca))
        {
            encontrados++;
            printf("\n---------------------------------------------\n");
            printf("Resultado %d\n", encontrados);
            mostrarFamilia(i);
        }
    }

    return encontrados;
}
// Função para editar os dependentes de uma família, permitindo adicionar, editar ou excluir dependentes, com validação de opções e mensagens caso não existam dependentes ou o limite seja atingido
void editarDependentes(int pos)
{
    int opcao;
    int indice;
    int i;

    do
    {
       LIMPAR_TELA();

        printf("--------------------------------------\n");
        printf("         EDITAR DEPENDENTES\n");
        printf("--------------------------------------\n");

        printf("Quantidade atual: %d\n\n",
               familias[pos].qtdDependentes);

        for(i = 0; i < familias[pos].qtdDependentes; i++)
        {
            printf("%d - %s\n",i + 1,familias[pos].dependentes[i].nome);
        }

        printf("\n");
        printf("1 - Editar dependente existente\n");
        printf("2 - Adicionar dependente\n");
        printf("3 - Remover dependente\n");
        printf("0 - Voltar\n");

        printf("\nOpção: ");
        opcao = lerOpcaoMenu(0, 3);

        switch(opcao)
        {
            case 1:

                if(familias[pos].qtdDependentes == 0)
                {
                    printf("Não existem dependentes.\n");
                    pausar();
                    break;
                }

                if(lerInteiro(&indice, "Número do dependente que deseja editar: ", 1, familias[pos].qtdDependentes) == 0)
                    break;

                indice--;

                if(indice >= 0 && indice < familias[pos].qtdDependentes)
                {
                    lerNome(familias[pos].dependentes[indice].nome,"Nome: ");

                    lerInteiro(&familias[pos].dependentes[indice].idade,"Idade: ",0,120);

                    lerSexo(familias[pos].dependentes[indice].sexo,"Sexo (F/M): ");

                    lerNome(familias[pos].dependentes[indice].parentesco,"Parentesco: ");

                    salvarDados();
                }

                break;

            case 2:

                if(familias[pos].qtdDependentes >= MAX_DEP)
                {
                    printf("Limite de dependentes atingido (máximo de %d).\n", MAX_DEP);
                    pausar();
                    break;
                }

                indice =
                    familias[pos].qtdDependentes;

                lerNome(
                    familias[pos].dependentes[indice].nome,"Nome: ");

                lerInteiro(&familias[pos].dependentes[indice].idade,"Idade: ",0,120);

                lerSexo(familias[pos].dependentes[indice].sexo,"Sexo (F/M): ");

                lerNome(familias[pos].dependentes[indice].parentesco,"Parentesco: ");

                familias[pos].qtdDependentes++;

                salvarDados();

                break;

           case 3:

                if(familias[pos].qtdDependentes == 0)
                {
                    printf("Não existem dependentes.\n");
                    pausar();
                    break;
                }

                if(lerInteiro(&indice, "Número do dependente que deseja excluir: ", 1, familias[pos].qtdDependentes) == 0)
                    break;

                indice--;

                if(indice >= 0 && indice < familias[pos].qtdDependentes)
                {
                    char confirmaExclusao[10];

                    printf("Tem certeza que deseja excluir o dependente \"%s\"? Digite sim ou não: ",
                           familias[pos].dependentes[indice].nome);

                    if(lerSimNao(confirmaExclusao, "") == 0 || confirmaExclusao[0] == 'n')
                    {
                        printf("Exclusão cancelada.\n");
                        pausar();
                        break;
                    }

                    for(i = indice;i < familias[pos].qtdDependentes - 1;i++)
                    {
                        familias[pos].dependentes[i] =familias[pos].dependentes[i + 1];
                    }

                    familias[pos].qtdDependentes--;

                    salvarDados();

                    printf("Dependente excluído com sucesso!\n");
                    pausar();
                }

                break;
        }

    } while(opcao != 0);
}
// Função para registrar a exclusão de uma família, salvando os dados da família e o motivo da exclusão em um arquivo de texto, com validação de abertura do arquivo
void registrarExclusao(Familia familia, char motivo[])
{
    FILE *arquivo;

    arquivo = fopen("historico_exclusoes.txt", "a");

    if(arquivo == NULL)
        return;

    fprintf(arquivo,"-------------------------------------------\n");

    fprintf(arquivo,"Ficha: %d\n",familia.ficha);
    fprintf(arquivo,"Nome: %s\n",familia.atendido.nome);
    fprintf(arquivo,"CPF: %s\n", familia.atendido.cpf);
    fprintf(arquivo,"Telefone: %s\n",familia.endereco.telefone);
    fprintf(arquivo, "Motivo da exclusão: %s\n",motivo);
    fprintf(arquivo,"-------------------------------------------\n\n");
    fclose(arquivo);
}

int main()
{

    setlocale(LC_ALL, "");

    int opcao = 0;
    int i, posicao;
    char busca[80];
    char confirmar;
    int fichaGerada;
// Carregar os dados das famílias do arquivo binário ao iniciar o programa
    carregarDados();
// Loop principal do programa, exibindo o menu e processando as opções escolhidas pelo usuário
    while(opcao != 7)
    {
        LIMPAR_TELA();

        printf("---------------------------------------------\n");
        printf("       SISTEMA VICENTINOS - SANTA CRUZ\n");
        printf("---------------------------------------------\n");
        printf("  1 - Cadastrar família\n");
        printf("  2 - Listar famílias cadastradas\n");
        printf("  3 - Consultar família por CPF\n");
        printf("  4 - Consultar família por nome\n");
        printf("  5 - Editar cadastro\n");
        printf("  6 - Excluir família\n");
        printf("  7 - Sair\n");
        printf("---------------------------------------------\n");
        printf("Escolha uma opção: ");
        opcao = lerOpcaoMenu(1, 7);
// Processar a opção escolhida pelo usuário, chamando as funções correspondentes para cada ação
        if(opcao == 1)
        {
            LIMPAR_TELA();

            if(total >= MAX)
            {
                printf("Limite de cadastros atingido (máximo de %d famílias).\n", MAX);
            }
            else
            {
                printf("---------------------------------------------\n");
                printf("          CADASTRO DE FAMÍLIA\n");
                printf("---------------------------------------------\n");
                printf("Conferência: Santa Cruz");

                fichaGerada = proximaFicha;

                if(cadastrarFamilia(total) == 1)
                {
                    total++;
                    salvarDados();
                    printf("\nCadastro realizado e salvo com sucesso!\n");
                }
                else
                {
                    proximaFicha = fichaGerada;
                    printf("\nCadastro cancelado. Voltando ao menu...\n");
                }
            }

            pausar();
        }// Listar todas as famílias cadastradas, mostrando o total de famílias ativas e o total de fichas geradas
        else if(opcao == 2)
        {
            LIMPAR_TELA();

            printf("---------------------------------------------\n");
            printf("        FAMÍLIAS CADASTRADAS\n");
            printf("---------------------------------------------\n\n");
            printf("Total de famílias ativas: %d\n", total);
            printf("Total de fichas já geradas no projeto: %d\n\n", proximaFicha - 1);

            if(total == 0)
            {
                printf("Nenhuma familia cadastrada.\n");
            }
            else
            {
                for(i = 0; i < total; i++)
                {
                    printf("---------------------------------------------\n");
                    printf("Ficha: %d\n", familias[i].ficha);
                    printf("Conferencia: %s\n", familias[i].conferencia);
                    printf("Nome: %s\n", familias[i].atendido.nome);
                    printf("CPF: %s\n", familias[i].atendido.cpf);
                    printf("Telefone: %s\n", familias[i].endereco.telefone);
                    printf("Bairro: %s\n", familias[i].endereco.bairro);
                    printf("Renda familiar: R$ %.2f\n", familias[i].financeiro.renda);
                }
            }

            pausar();
        }// Consultar uma família por CPF, mostrando os dados da família se encontrada, ou uma mensagem caso não exista
        else if(opcao == 3)
        {
            LIMPAR_TELA();

            printf("Digite o CPF: ");
            scanf(" %79[^\n]", busca);

            posicao = buscarPorCPF(busca);

            if(posicao == -1)
                printf("\nFamília não encontrada.\n");
            else
                mostrarFamilia(posicao);

            pausar();
        }// Consultar famílias por nome, listando todas as famílias que contenham o nome ou parte dele, ou uma mensagem caso não exista
        else if(opcao == 4)
        {
            LIMPAR_TELA();

            printf("Digite o nome ou parte do nome: ");
            scanf(" %79[^\n]", busca);

            // Em vez de mostrar apenas o primeiro nome encontrado, agora lista todas as familias que tenham esse nome ou parte dele.
            if(listarFamiliasPorNome(busca) == 0)
                printf("\nFamília não encontrada.\n");

            pausar();
        }// Editar o cadastro de uma família, permitindo alterar os dados do atendido, endereço, companheiro, estado civil, dependentes, religião, financeiro, saúde e controle, com confirmação antes de editar
        else if(opcao == 5)
        {
            LIMPAR_TELA();

            printf("Digite o CPF da família que deseja editar: ");
            scanf(" %79[^\n]", busca);

            posicao = buscarPorCPF(busca);

            if(posicao == -1)
            {
                printf("\nFamília não encontrada.\n");
            }
            else
            {


                printf("\nCadastro encontrado:\n");
                printf("Ficha: %d\n", familias[posicao].ficha);
                printf("Nome: %s\n", familias[posicao].atendido.nome);
                printf("CPF: %s\n", familias[posicao].atendido.cpf);

                printf("\nDeseja editar este cadastro? (S/N): ");
                scanf(" %c", &confirmar);

            if(confirmar == 'S' || confirmar == 's')
            {int opcaoEdicao;

        do
    {
        LIMPAR_TELA();

            printf("-------------------------------------\n");
            printf("      EDITAR CADASTRO\n");
            printf("------------------------------------\n");

            printf("1 - Dados do atendido\n");
            printf("2 - Endereço\n");
            printf("3 - Companheiro\n");
            printf("4 - Estado civil\n");
            printf("5 - Dependentes\n");
            printf("6 - Religião\n");
            printf("7 - Financeiro\n");
            printf("8 - Saúde\n");
            printf("9 - Controle\n");
            printf("0 - Voltar\n");

    printf("\nOpção: ");
    opcaoEdicao = lerOpcaoMenu(0, 9);
// Processar a opção de edição escolhida pelo usuário, chamando as funções correspondentes para cada ação
    switch(opcaoEdicao)
    {
        case 1:
                lerNome(familias[posicao].atendido.nome,"Nome: ");
                lerInteiro(&familias[posicao].atendido.idade,"Idade: ",0,120);
                salvarDados();
                break;

        case 2:
                lerEndereco(familias[posicao].endereco.endereco,"Endereço: ");
                lerNumeroCasa(familias[posicao].endereco.numero);
                lerNome(familias[posicao].endereco.bairro,"Bairro: ");
                salvarDados();
                break;

        case 3:
                if(familias[posicao].possuiCompanheiro[0] == 's')
                {lerNome(familias[posicao].esposo.nome,"Nome: ");
                lerInteiro(&familias[posicao].esposo.idade,"Idade: ",0,120);
                salvarDados();
                } else
                {printf("Esta família não possui companheiro(a).\n");
                pausar();
                }
                break;

        case 4:

                if(familias[posicao].possuiCompanheiro[0] == 's')
                {lerSimNao(familias[posicao].estadoCivil.casadosCivil,"Casados no civil? ");
                lerSimNao(familias[posicao].estadoCivil.casadosIgreja,"Casados na igreja? ");
                salvarDados();
                } else
                {printf("Estado civil indisponível.\n");
                pausar();
                }
                break;

        case 5:
                editarDependentes(posicao);
                break;

        case 6:
                lerSimNao(familias[posicao].religiao.catolicos,"São católicos? ");
                salvarDados();
                break;

        case 7:
                lerFloat(&familias[posicao].financeiro.renda,"Renda familiar: ");
                salvarDados();
                break;

        case 8:
                lerSimNao(familias[posicao].saude.haDoentes,"Há doentes? ");
                salvarDados();
                break;

        case 9:
                lerSimNao(familias[posicao].controle.necessitaAdotada,"Necessita ser adotada? ");
                salvarDados();
                break;

    }


      } while(opcaoEdicao != 0);
        pausar();
            }
            }

// Excluir uma família, solicitando o CPF da família a ser excluída, confirmando a exclusão e registrando o motivo da exclusão em um arquivo de histórico
        }else if(opcao == 6)
        {

            LIMPAR_TELA();

            printf("Digite o CPF da família que deseja excluir: ");
            scanf(" %79[^\n]", busca);

            posicao = buscarPorCPF(busca);

            if(posicao == -1)
            {
                printf("\nFamília não encontrada.\n");
            }
        else
            {
            int motivoEscolhido;
            char motivo[200];

            printf("\nMotivo da exclusão:\n");
            printf("1 - Não precisa mais de ajuda\n");
            printf("2 - Mudou de endereço\n");
            printf("3 - Falecimento\n");
            printf("4 - Cadastro duplicado\n");
            printf("5 - Outro motivo\n");
            printf("\nEscolha: ");
            motivoEscolhido = lerOpcaoMenu(1, 5);
// Registrar o motivo da exclusão com base na escolha do usuário, permitindo a entrada de um motivo personalizado se necessário
    switch(motivoEscolhido)
        {
            case 1:
            strcpy(motivo,"Não precisa mais de ajuda");
            break;

            case 2:
            strcpy(motivo,"Mudou de endereço");
            break;

            case 3:
            strcpy(motivo,"Falecimento");
            break;

            case 4:
            strcpy(motivo,"Cadastro duplicado");
            break;

            case 5:
            printf("Digite o motivo: ");
            scanf(" %199[^\n]", motivo);
            break;

    default:
            strcpy(motivo,"Motivo não informado");
}
        printf("\nDeseja realmente excluir esta família? (S/N): ");
        scanf(" %c", &confirmar);

        if(confirmar == 'S' || confirmar == 's')
        {
            registrarExclusao(familias[posicao],motivo);

            for(i = posicao; i < total - 1; i++)
                {
                familias[i] = familias[i + 1];
                }

            total--;
            salvarDados();

            printf("\nFamília excluída com sucesso!\n");
            printf("A numeração das próximas fichas continuará normalmente.\n");
                }
            else
                {
                    printf("\nExclusão cancelada.\n");
                }
            }
                pausar();
            }
            else if(opcao == 7)
            {
                salvarDados();

            LIMPAR_TELA();
            printf("---------------------------------------------\n");
            printf("      Dados salvos com sucesso!\n");
            printf("      Obrigado por utilizar o sistema.\n");
            printf("---------------------------------------------\n");
        }
        else
        {
            printf("\nOpção inválida.\n");
            pausar();
        }
    }


    return 0;


}
