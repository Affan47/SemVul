eval_grd_uh(const REAL lambda[N_LAMBDA],
			const REAL_D Lambda[N_LAMBDA],
			const REAL *uh_loc, const BAS_FCTS *b, REAL_D grd_uh)
{
  static REAL_D  grd;
  const REAL     *grd_b;
  int            i, j, dim = b->dim;
  GRD_BAS_FCT    **grd_phi = b->grd_phi;
  REAL           *val, grd1[N_LAMBDA] = {0};

  val = grd_uh ? grd_uh : grd;

  for (i = 0; i < b->n_bas_fcts; i++)
  {
    grd_b = grd_phi[i](lambda);
    for (j = 0; j < dim+1; j++)
      grd1[j] += uh_loc[i]*grd_b[j];
  }

  for (i = 0; i < DIM_OF_WORLD; i++)
  {
    for (val[i] = j = 0; j < dim+1; j++)
      val[i] += Lambda[j][i]*grd1[j];
  }

  return((const REAL *) val);
}
