eval_D2_uh(const REAL lambda[N_LAMBDA],
			 const REAL_D Lambda[N_LAMBDA],
			 const REAL *uh_loc, const BAS_FCTS *b, REAL_DD D2_uh)
{
  static REAL_DD D2;
  const REAL     (*D2_b)[N_LAMBDA];
  int            i, j, k, l, dim = b->dim;
  D2_BAS_FCT     **D2_phi = b->D2_phi;
  REAL           (*val)[DIM_OF_WORLD], D2_tmp[N_LAMBDA][N_LAMBDA] = {{0}};

  val = D2_uh ? D2_uh : D2;

  for (i = 0; i < b->n_bas_fcts; i++)
  {
    D2_b = D2_phi[i](lambda);
    for (k = 0; k < dim+1; k++)
      for (l = k; l < dim+1; l++)
      D2_tmp[k][l] += uh_loc[i]*D2_b[k][l];
  }

  for (i = 0; i < DIM_OF_WORLD; i++)
    for (j = i; j < DIM_OF_WORLD; j++)
    {
      val[i][j] = 0.0;
      for (k = 0; k < dim+1; k++)
      {
	val[i][j] += Lambda[k][i]*Lambda[k][j]*D2_tmp[k][k];
	for (l = k+1; l < dim+1; l++)
	  val[i][j] +=
	    (Lambda[k][i]*Lambda[l][j] + Lambda[l][i]*Lambda[k][j])*D2_tmp[k][l];
      }
      val[j][i] = val[i][j];
  }

  return((const REAL_D *) val);
}
