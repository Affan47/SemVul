create_multi_NUBspline_1d_z (NUgrid* x_grid, BCtype_z xBC, int num_splines)
{

  multi_NUBspline_1d_z* restrict spline = malloc (sizeof(multi_NUBspline_1d_z));
  spline->spcode = MULTI_NU1D;
  spline->tcode  = DOUBLE_COMPLEX;
  spline->xBC = xBC;
  spline->x_grid = x_grid;
  spline->num_splines = num_splines;


  spline->x_basis = create_NUBasis (x_grid, xBC.lCode==PERIODIC);

  if (spline->x_basis->grid != x_grid) {
    fprintf (stderr, "Error in basis creation.\n");
    abort();
  }
  if (spline->x_basis == NULL) {
    fprintf (stderr, "Error creating basis in create_multi_NUBspline_1d_z.\n");
    abort();
  }


  int Mx, Nx;
  if (xBC.lCode == PERIODIC)     Mx = x_grid->num_points - 1;
  else                           Mx = x_grid->num_points;
  Nx = x_grid->num_points + 2;

  int N = num_splines;
#ifdef HAVE_SSE
  if (N % 2)
    N ++;
#endif

  spline->x_stride = N;
#ifndef HAVE_SSE2
  spline->coefs = malloc (2*sizeof(double)*Nx*N);
#else
  posix_memalign ((void**)&spline->coefs, 64, 2*sizeof(double)*Nx*N);
  init_sse_data();
#endif

  return spline;
}
