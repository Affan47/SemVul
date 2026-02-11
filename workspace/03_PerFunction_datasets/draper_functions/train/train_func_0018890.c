create_multi_UBspline_2d_z (Ugrid x_grid, Ugrid y_grid,
		      BCtype_z xBC, BCtype_z yBC, int num_splines)
{

  multi_UBspline_2d_z* restrict spline = malloc (sizeof(multi_UBspline_2d_z));
  spline->spcode = MULTI_U2D;
  spline->tcode  = DOUBLE_COMPLEX;
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
  spline->x_stride = Ny*num_splines;
  spline->y_stride = num_splines;

#ifndef HAVE_SSE2
  spline->coefs = malloc (2*sizeof(double)*Nx*Ny*num_splines);
  spline->lapl2 = malloc (4*sizeof(double)*num_splines);
#else
  posix_memalign ((void**)&spline->coefs, 64, 2*sizeof(double)*Nx*Ny*num_splines);
  posix_memalign ((void**)&spline->lapl2, 64, 4*sizeof(double)*num_splines);

  init_sse_data();
#endif

  return spline;
}
