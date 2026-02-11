direct(int n)
{


  memset(&(egrid[n][nzlo_out[n]][nylo_out[n]][nxlo_out[n]]),0,ngrid[n]*sizeof(double));


  if (vflag_atom) {
    memset(&(v0grid[n][nzlo_out[n]][nylo_out[n]][nxlo_out[n]]),0,ngrid[n]*sizeof(double));
    memset(&(v1grid[n][nzlo_out[n]][nylo_out[n]][nxlo_out[n]]),0,ngrid[n]*sizeof(double));
    memset(&(v2grid[n][nzlo_out[n]][nylo_out[n]][nxlo_out[n]]),0,ngrid[n]*sizeof(double));
    memset(&(v3grid[n][nzlo_out[n]][nylo_out[n]][nxlo_out[n]]),0,ngrid[n]*sizeof(double));
    memset(&(v4grid[n][nzlo_out[n]][nylo_out[n]][nxlo_out[n]]),0,ngrid[n]*sizeof(double));
    memset(&(v5grid[n][nzlo_out[n]][nylo_out[n]][nxlo_out[n]]),0,ngrid[n]*sizeof(double));
  }

  if (eflag_global) {
    if (vflag_global) {
      if (vflag_atom)
        direct_eval<1,1,1>(n);
      else
        direct_eval<1,1,0>(n);
    } else {
      if (vflag_atom)
        direct_eval<1,0,1>(n);
      else
        direct_eval<1,0,0>(n);
    }
  } else {
    if (vflag_global) {
      if (vflag_atom)
        direct_eval<0,1,1>(n);
      else
        direct_eval<0,1,0>(n);
    } else {
      if (vflag_atom)
        direct_eval<0,0,1>(n);
      else
        direct_eval<0,0,0>(n);
    }
  }

  if (vflag_atom)
    direct_peratom<1>(n);
  else
    direct_peratom<0>(n);
}
