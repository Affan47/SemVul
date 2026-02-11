answer(double *m, double *b, int *n)
{
  int c=0, k=0;
  double *x,temp;
  FILE *Pfile;

  x = malloc(*n *sizeof(double));


  for(c=*n-1; c>=0; c--)
  {
    temp = 0;
    for(k=*n-1; k>c; k--)
    {


      temp += m[*n *c+k]*x[k];
    }
      x[c]= (b[c]-temp)/(m[*n *c+c]);
  }

  Pfile = fopen("gauss_answer.out","w");

  for(c=0; c<*n; c++)
  {
    fprintf(Pfile,"%f\n",x[c]);
  }

  free (x);
  fclose (Pfile);

return;
}
