#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


typedef struct tree{
  int value; /* valeur de l'operande */
  char operator; /* operateur */
  struct tree *left; /* sous-arbre gauche */
  struct tree *right; /* sous-arbre droite */
} node_t;


/*  Construction de l'arbre binaire */
node_t *build_tree(char **argv, int *position){

  node_t *p = malloc(sizeof(node_t));

  switch (*(*(argv+*position))) {

    case '+':
    p->operator = '+';
    (*position) ++;
    p->left = build_tree(argv,position);
    (*position) ++;
    p->right = build_tree(argv,position);
    break;

    case '-':
    p->operator = '-';
    (*position) ++;
    p->left = build_tree(argv,position);
    (*position) ++;
    p->right = build_tree(argv,position);
    break;

    case '*':
    p->operator = '*';
    (*position) ++;
    p->left = build_tree(argv,position);
    (*position) ++;
    p->right = build_tree(argv,position);
    break;

    case '/':
    p->operator = '/';
    (*position) ++;
    p->left = build_tree(argv,position);
    (*position) ++;
    p->right = build_tree(argv,position);
    break;

    default :
    p->value = atoi(*(argv+*position));
    p->left = NULL;
    p->right = NULL;
  }
  return p;
}

/* En utilisant la recursivite de la structure, affichez l'arbre sous forme infixe :
on trouve un nombre, on l'affiche, sinon on accède aux sous arbres pour afficher le
sous abre de gauche, puis l'operateur, puis le sous arbre de droite */

void print_infix(node_t* n){
  if (n->left == NULL && n->right == NULL) {
    printf("%d",n->value);
  }
  else {
    printf("(");
    print_infix(n->left);
    printf("%c",n->operator);
    print_infix(n->right);
    printf(")");
  }
}

/* Calcul du resultat, toujours grace a la recursivite, si c'est un nombre, c'est le
resultat que retourne la fonction, sinon si c'est un operateur on evalue les sous arbres
qui seront les operandes de cet operateur */

int compute_tree(node_t *root){
  int res = 0;
  if (root->right == NULL && root->left == NULL){
    res = root->value;
  }
  else {
    int x = compute_tree(root->left);
    int y = compute_tree(root->right);
    switch (root->operator){
      case '+':
        res=x+y;
      break;

      case '-':
        res=x-y;
      break;

      case '*':
        res=x*y;
      break;

      case '/':
        res=x/y;
      break;
    }
  }
  return res;
}

int main(int argc,char **argv) {
  node_t *root = malloc(sizeof(root));
  int position = 1;
  root=build_tree(argv,&position);
  print_infix(root);
  printf("=%i \n",compute_tree(root));
  return 0;
}
