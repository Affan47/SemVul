create_UBspline_2d_d (Ugrid x_grid, Ugrid y_grid,
		      BCtype_d xBC, BCtype_d yBC, double *data)
{

  UBspline_2d_d* restrict spline = malloc (sizeof(UBspline_2d_d));
  spline->spcode = U2D;
  spline->tcode  = DOUBLE_REAL;
  spline->xBC = xBC;
  spline->yBC = yBC;


  int Mx = x_grid.num;
  int My = y_grid.num;
  int Nx, Ny;

  if (xBC.lCode == PERIODIC || xBC.lCode == ANTIPERIODIC)     Nx = Mx+3;
  else                           Nx = Mx+2;
  x_grid.delta = (x_grid.end - x_grid.start)/(double)(Nx-3);
  x_grid.delta_inv = 1.0/x_grid.delta;
  spline->x_grid   = x_grid;

  if (yBC.lCode == PERIODIC || yBC.lCode == ANTIPERIODIC)     Ny = My+3;
  else                           Ny = My+2;
  y_grid.delta = (y_grid.end - y_grid.start)/(double)(Ny-3);
  y_grid.delta_inv = 1.0/y_grid.delta;
  spline->y_grid   = y_grid;
  spline->x_stride = Ny;

#ifndef HAVE_SSE2
  spline->coefs = malloc (sizeof(double)*Nx*Ny);
#else
  posix_memalign ((void**)&spline->coefs, 16, (sizeof(double)*Nx*Ny));
#endif


  for (int iy=0; iy<My; iy++) {
    intptr_t doffset = iy;
    intptr_t coffset = iy;
    find_coefs_1d_d (spline->x_grid, xBC, data+doffset, My,
		     spline->coefs+coffset, Ny);
  }


  for (int ix=0; ix<Nx; ix++) {
    intptr_t doffset = ix*Ny;
    intptr_t coffset = ix*Ny;
    find_coefs_1d_d (spline->y_grid, yBC, spline->coefs+doffset, 1,
		     spline->coefs+coffset, 1);
  }

  init_sse_data();
  return spline;
}
