diag_precon_d(void *ud, int dim, REAL *r)
{
  FUNCNAME("diag_precon_d");
  struct precon_data  *data = (struct precon_data *)ud;
  int                 i, n;
  const REAL          *diag_1 = data->diag_1;
  REAL_D              *rd = (REAL_D *) r;

  DEBUG_TEST_EXIT(dim == data->dim*DIM_OF_WORLD,
		  "argument dim != precon_data->dim*DIM_OF_WORLD\n");

  for (i = 0; i < data->dim; i++)
  {
    for (n = 0; n < DIM_OF_WORLD; n++)
      rd[i][n] *= diag_1[i];
  }

  return;
}
