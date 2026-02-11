matfree(float **mat)
{
  int i;

  for(i=0;i<MSIZE;i++)
    free(mat[i]);

  free(mat);
}
