pack_comm(int n, int *list, double *buf, int pbc_flag, int *pbc)
{
  int i,j,m;

  m = 0;
  if (rhofp == 1) {
    for (i = 0; i < n; i++) {
      j = list[i];
      buf[m++] = rho[j];
    }
  }
  if (rhofp == 2) {
    for (i = 0; i < n; i++) {
      j = list[i];
      buf[m++] = fp[j];
    }
  }
  return 1;
}
