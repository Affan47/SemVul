print_matrix(double *m, int *n)
{
  double buffer;
  int i=0, k=0;
  FILE *matrix;


  matrix = fopen("gauss_mat.out","w");

  for(i=0; i<*n; i++)
  {
    for(k=0; k<*n; k++)
    {
      buffer = m[*n *i+k];
      fprintf(matrix,"%f\t",buffer);
    }
    fprintf(matrix,"\n");
  }

  fclose (matrix);

return;
}
