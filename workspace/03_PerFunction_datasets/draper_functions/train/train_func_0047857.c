matrix_clear(matrix_t* mat)
{
  size_t i,j;
  for (i=0; i<mat->nbrows; i++){
    for (j=0; j<mat->nbcolumns; j++){
      numint_set_int(mat->p[i][j],0);
      }
  }
}
