eval_grd_uh_d_fast(const REAL_D Lambda[N_LAMBDA],
				 const REAL_D *uh_loc,
				 const REAL (*grd_phi)[N_LAMBDA],
				 int n_bas_fcts, REAL_DD grd_uh)
{
  static REAL_DD  grd;
  int             i, j, n;
  REAL_D          *val;
  REAL            grd1[N_LAMBDA];

  val = grd_uh ? grd_uh : grd;

  for (n = 0; n < DIM_OF_WORLD; n++)
  {
    for (j = 0; j < N_LAMBDA; j++)
      grd1[j] = 0.0;

    for (i = 0; i < n_bas_fcts; i++)
    {
      for (j = 0; j < N_LAMBDA; j++)
	grd1[j] += uh_loc[i][n]*grd_phi[i][j];
    }

    for (i = 0; i < DIM_OF_WORLD; i++)
    {
      for (val[n][i] = j = 0; j < N_LAMBDA; j++)
	val[n][i] += Lambda[j][i]*grd1[j];
    }
  }

  return((const REAL_D *) val);
}
