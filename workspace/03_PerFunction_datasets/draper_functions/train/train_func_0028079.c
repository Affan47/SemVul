satmat_copy_resize_cols(satmat_t* sat, size_t nbcols)
{
  size_t i,j;
  satmat_t* nsat;

  assert(nbcols>=sat->nbcolumns);
  nsat = satmat_alloc(sat->nbrows,nbcols);
  for (i=0; i<sat->nbrows; i++){
    for (j=0; j<sat->nbcolumns; j++){
      nsat->p[i][j] = sat->p[i][j];
    }
    for (j=sat->nbcolumns; j<nbcols; j++)
      nsat->p[i][j] = 0;
  }
  return nsat;
}
