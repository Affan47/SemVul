print_matrix_f( float **v, int m, int n, char *t)
{
  int i,j;
  if(v==NULL)
    {
      printf("\npointer passed is null for %s\n",t);
      return;
    }
  printf("\nmatrix %s, m,n=%d %d\n",t,m,n);
  for(i=0;i<m;i++) {
    if(i==3 && i+200<m)
      printf(".\n.\n.\nskipping to %d\n",i+=200);
    printf("\n row %d\n",i);
    for(j=0;j<n;j++) {
      printf(" %g ",v[i][j]);
    }
  }
  printf("\n");
}
