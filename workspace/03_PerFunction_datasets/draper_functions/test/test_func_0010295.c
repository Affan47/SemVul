create_multi_NUBspline_1d_s (NUgrid* x_grid, BCtype_s xBC, int num_splines)
{

  multi_NUBspline_1d_s* restrict spline = malloc (sizeof(multi_NUBspline_1d_s));
  if (spline == NULL)
    return spline;

  spline->spcode = MULTI_NU1D;
  spline->tcode  = SINGLE_REAL;


  spline->x_basis = create_NUBasis (x_grid, xBC.lCode==PERIODIC);
  spline->xBC = xBC; spline->x_grid = x_grid;
  spline->num_splines = num_splines;


  int Mx, Nx;
  if (xBC.lCode == PERIODIC)     Mx = x_grid->num_points - 1;
  else                           Mx = x_grid->num_points;
  Nx = x_grid->num_points + 2;

  int N = num_splines;
#ifdef HAVE_SSE
  if (N % 4)
    N += 4 - (N % 4);
#endif

  spline->x_stride = N;
  spline->x_grid   = x_grid;
#ifndef HAVE_SSE
  spline->coefs = malloc (sizeof(float)*Nx*N);
#else
  posix_memalign ((void**)&spline->coefs, 64, (sizeof(float)*Nx*N));
  init_sse_data();
#endif

  return spline;
}
