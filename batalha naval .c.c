#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAMANHO_TABULEIRO 5
#define TAMANHO_NAVIO 3

void imprimirTabuleiro(char tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
  printf("  ");
  for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
    printf("%d ", i);
  }
  printf("\n");
  for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
    printf("%d ", i);
    for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
      printf("%c ", tabuleiro[i][j]);
    }
    printf("\n");
  }
}

int main() {
  char tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
  int linhaNavio, colunaNavio;
  int linhaPalpite, colunaPalpite;
  int tentativas = 0;
  int maxTentativas = 10;
  int partesAcertadas = 0;
  int direcaoNavio;

  // Inicializa o gerador de números aleatórios
  srand(time(NULL));

  // Inicializa o tabuleiro com água ('~')
  for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
    for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
      tabuleiro[i][j] = '~';
    }
  }

  // Posiciona o navio em uma localização aleatória e direção aleatória
  direcaoNavio = rand() % 2; // 0 para horizontal, 1 para vertical
  if (direcaoNavio == 0) {   // horizontal
    linhaNavio = rand() % TAMANHO_TABULEIRO;
    colunaNavio = rand() % (TAMANHO_TABULEIRO - TAMANHO_NAVIO + 1);
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
      tabuleiro[linhaNavio][colunaNavio + i] = 'N';
    }
  } else { // vertical
    linhaNavio = rand() % (TAMANHO_TABULEIRO - TAMANHO_NAVIO + 1);
    colunaNavio = rand() % TAMANHO_TABULEIRO;
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
      tabuleiro[linhaNavio + i][colunaNavio] = 'N';
    }
  }

  // Converte células do navio para '~' para ocultar a posição
  for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
    for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
      if (tabuleiro[i][j] == 'N') {
        tabuleiro[i][j] = '~';
      }
    }
  }

  printf("Bem-vindo ao Batalha Naval!\n");
  printf("Você tem %d tentativas para encontrar o navio de %d células.\n",
         maxTentativas, TAMANHO_NAVIO);

  // Laço principal do jogo
  while (tentativas < maxTentativas && partesAcertadas < TAMANHO_NAVIO) {
    imprimirTabuleiro(tabuleiro);
    printf("Digite seu palpite (linha e coluna): ");
    scanf("%d %d", &linhaPalpite, &colunaPalpite);

    // Verifica se o palpite é válido
    if (linhaPalpite < 0 || linhaPalpite >= TAMANHO_TABULEIRO ||
        colunaPalpite < 0 || colunaPalpite >= TAMANHO_TABULEIRO) {
      printf("Entrada inválida. Por favor, insira números entre 0 e %d.\n",
             TAMANHO_TABULEIRO - 1);
      continue;
    }

    // Verifica o resultado do palpite
    switch (tabuleiro[linhaPalpite][colunaPalpite]) {
    case '~':
      tentativas++;
      if (direcaoNavio == 0) { // horizontal
        if (linhaPalpite == linhaNavio && colunaPalpite >= colunaNavio &&
            colunaPalpite < colunaNavio + TAMANHO_NAVIO) {
          printf("Acertou uma parte do navio!\n");
          tabuleiro[linhaPalpite][colunaPalpite] = 'N';
          partesAcertadas++;
        } else {
          printf("Errou.\n");
          tabuleiro[linhaPalpite][colunaPalpite] = 'X';
        }
      } else { // vertical
        if (colunaPalpite == colunaNavio && linhaPalpite >= linhaNavio &&
            linhaPalpite < linhaNavio + TAMANHO_NAVIO) {
          printf("Acertou uma parte do navio!\n");
          tabuleiro[linhaPalpite][colunaPalpite] = 'N';
          partesAcertadas++;
        } else {
          printf("Errou.\n");
          tabuleiro[linhaPalpite][colunaPalpite] = 'X';
        }
      }
      break;
    default:
      printf("Você já adivinhou essa localização. Tente novamente.\n");
      break;
    }
  }

  if (partesAcertadas == TAMANHO_NAVIO) {
    printf("Parabéns! Você afundou o navio!\n");
  } else {
    printf("Fim de jogo! Você usou todas as suas tentativas.\n");
    printf("O navio estava em:\n");
    if (direcaoNavio == 0) { // horizontal
      for (int i = 0; i < TAMANHO_NAVIO; i++) {
        printf("(%d, %d)\n", linhaNavio, colunaNavio + i);
      }
    } else { // vertical
      for (int i = 0; i < TAMANHO_NAVIO; i++) {
        printf("(%d, %d)\n", linhaNavio + i, colunaNavio);
      }
    }
  }

  imprimirTabuleiro(tabuleiro);
  return 0;
}
