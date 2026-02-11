create_multi_UBspline_2d_c (Ugrid x_grid, Ugrid y_grid,
			    BCtype_c xBC, BCtype_c yBC, int num_splines)
{

  multi_UBspline_2d_c* restrict spline = malloc (sizeof(multi_UBspline_2d_c));
  spline->spcode = MULTI_U2D;
  spline->tcode  = SINGLE_COMPLEX;
  spline->xBC = xBC;
  spline->yBC = yBC;
  spline->num_splines = num_splines;


  int Mx = x_grid.num;
  int My = y_grid.num;
  int Nx, Ny;

  if (xBC.lCode == PERIODIC || xBC.lCode == ANTIPERIODIC)
    Nx = Mx+3;
  else
    Nx = Mx+2;
  x_grid.delta = (x_grid.end - x_grid.start)/(double)(Nx-3);
  x_grid.delta_inv = 1.0/x_grid.delta;
  spline->x_grid   = x_grid;

  if (yBC.lCode == PERIODIC || yBC.lCode == ANTIPERIODIC)
    Ny = My+3;
  else
    Ny = My+2;
  y_grid.delta = (y_grid.end - y_grid.start)/(double)(Ny-3);
  y_grid.delta_inv = 1.0/y_grid.delta;
  spline->y_grid   = y_grid;

  int N = num_splines;
#ifdef HAVE_SSE
  if (N % 2)
    N++;
#endif

  spline->x_stride = Ny*N;
  spline->y_stride = N;

#ifndef HAVE_SSE
  spline->coefs = malloc (2*sizeof(float)*Nx*Ny*N);
  spline->lapl2 = malloc (4*sizeof(float)*N);
#else
  posix_memalign ((void**)&spline->coefs, 64,
		  2*sizeof(float)*Nx*Ny*N);
  posix_memalign ((void**)&spline->lapl2, 64,
		  4*sizeof(float)*N);
#endif
  init_sse_data();

  return spline;
}
