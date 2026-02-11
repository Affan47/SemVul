pack_reverse(int flag, double *buf, int nlist, int *list)
{
  int n = current_level;

  double ***qgridn = qgrid[n];
  double ***egridn = egrid[n];

  double ***v0gridn = v0grid[n];
  double ***v1gridn = v1grid[n];
  double ***v2gridn = v2grid[n];
  double ***v3gridn = v3grid[n];
  double ***v4gridn = v4grid[n];
  double ***v5gridn = v5grid[n];

  int k = 0;

  if (flag == REVERSE_RHO) {
    double *qsrc = &qgridn[nzlo_out[n]][nylo_out[n]][nxlo_out[n]];
    for (int i = 0; i < nlist; i++) {
      buf[k++] = qsrc[list[i]];
    }
  } else if (flag == REVERSE_AD) {
    double *src = &egridn[nzlo_out[n]][nylo_out[n]][nxlo_out[n]];
    for (int i = 0; i < nlist; i++)
      buf[i] = src[list[i]];
  } else if (flag == REVERSE_AD_PERATOM) {
    double *v0src = &v0gridn[nzlo_out[n]][nylo_out[n]][nxlo_out[n]];
    double *v1src = &v1gridn[nzlo_out[n]][nylo_out[n]][nxlo_out[n]];
    double *v2src = &v2gridn[nzlo_out[n]][nylo_out[n]][nxlo_out[n]];
    double *v3src = &v3gridn[nzlo_out[n]][nylo_out[n]][nxlo_out[n]];
    double *v4src = &v4gridn[nzlo_out[n]][nylo_out[n]][nxlo_out[n]];
    double *v5src = &v5gridn[nzlo_out[n]][nylo_out[n]][nxlo_out[n]];
    for (int i = 0; i < nlist; i++) {
      buf[k++] = v0src[list[i]];
      buf[k++] = v1src[list[i]];
      buf[k++] = v2src[list[i]];
      buf[k++] = v3src[list[i]];
      buf[k++] = v4src[list[i]];
      buf[k++] = v5src[list[i]];
    }
  }
}
