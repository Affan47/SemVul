create_NUBspline_1d_s (NUgrid* x_grid, BCtype_s xBC, float *data)
{

  NUBspline_1d_s* spline = malloc (sizeof(NUBspline_1d_s));
  if (spline == NULL)
    return spline;
  spline->sp_code = NU1D;
  spline->t_code  = SINGLE_REAL;


  spline->x_basis = create_NUBasis (x_grid, xBC.lCode==PERIODIC);

  int M;
  if (xBC.lCode == PERIODIC) M = x_grid->num_points - 1;
  else                       M = x_grid->num_points;
  int N = x_grid->num_points + 2;


  spline->coefs = malloc(N*sizeof(float));
  find_NUBcoefs_1d_s (spline->x_basis, xBC, data, 1, spline->coefs, 1);

  return spline;
}
