set_multi_NUBspline_3d_s (multi_NUBspline_3d_s* spline, int num, float *data)
{
  int Mx, My, Mz, Nx, Ny, Nz;
  if (spline->xBC.lCode == PERIODIC) Mx = spline->x_grid->num_points - 1;
  else                               Mx = spline->x_grid->num_points;
  if (spline->yBC.lCode == PERIODIC) My = spline->y_grid->num_points - 1;
  else                               My = spline->y_grid->num_points;
  if (spline->zBC.lCode == PERIODIC) Mz = spline->z_grid->num_points - 1;
  else                               Mz = spline->z_grid->num_points;

  Nx = spline->x_grid->num_points + 2;
  Ny = spline->y_grid->num_points + 2;
  Nz = spline->z_grid->num_points + 2;

  float *coefs = spline->coefs + num;

  int zs = spline->z_stride;

  for (int iy=0; iy<My; iy++)
    for (int iz=0; iz<Mz; iz++) {
      int doffset = iy*Mz+iz;
      int coffset = (iy*Nz+iz)*zs;
      find_NUBcoefs_1d_s (spline->x_basis, spline->xBC, data+doffset, My*Mz,
			  coefs+coffset, Ny*Nz*zs);
    }


  for (int ix=0; ix<Nx; ix++)
    for (int iz=0; iz<Nz; iz++) {
      int doffset = (ix*Ny*Nz + iz)*zs;
      int coffset = (ix*Ny*Nz + iz)*zs;
      find_NUBcoefs_1d_s (spline->y_basis, spline->yBC, coefs+doffset, Nz*zs,
			  coefs+coffset, Nz*zs);
    }


  for (int ix=0; ix<Nx; ix++)
    for (int iy=0; iy<Ny; iy++) {
      int doffset = ((ix*Ny+iy)*Nz)*zs;
      int coffset = ((ix*Ny+iy)*Nz)*zs;
      find_NUBcoefs_1d_s (spline->z_basis, spline->zBC, coefs+doffset, zs,
			  coefs+coffset, zs);
    }
}
