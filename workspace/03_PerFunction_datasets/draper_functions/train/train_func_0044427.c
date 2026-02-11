copy_uo_vec(int inum, double **f, double **torque,
                                 double *RU)
{
  int i,j,ii;
  int *ilist;

  ilist = list->ilist;

  for (ii=0;ii<inum;ii++) {
    i = ilist[ii];
    for (j=0;j<3;j++) {
      RU[6*ii+j] = f[i][j];
      RU[6*ii+j+3] = torque[i][j];
    }
  }
}
