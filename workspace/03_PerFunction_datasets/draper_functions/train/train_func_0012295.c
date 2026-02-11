transposerMatrice(matrice *matriceA)
{
     int i,j;

     char nouveauNom[255];
     strcpy(nouveauNom,matriceA->nom);
     strcat(nouveauNom," transposee");


     matrice *transposee=creer_matrice(nouveauNom, matriceA->nb_lignes, matriceA->nb_colonnes,NON_SYMETRIQUE, INVERSIBLE, POSITIVE);

     for(i=0;i<matriceA->nb_lignes;i++)
          for (j=0;j<matriceA->nb_colonnes;j++)
               transposee->tableau_2d[i][j]=matriceA->tableau_2d[j][i];

     return transposee;
}
