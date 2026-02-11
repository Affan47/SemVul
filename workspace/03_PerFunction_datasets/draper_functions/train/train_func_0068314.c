gfs_advection_params_write (GfsAdvectionParams * par, FILE * fp)
{
  g_return_if_fail (par != NULL);
  g_return_if_fail (fp != NULL);

  fprintf (fp,
           "{\n"
	   "  cfl      = %g\n"
	   "  gradient = %s\n"
	   "  flux     = %s\n"
	   "  average  = %d\n",
	   par->cfl,
	   par->gradient == gfs_center_gradient ?
	   "gfs_center_gradient" :
	   par->gradient == gfs_center_van_leer_gradient ?
	   "gfs_center_van_leer_gradient" :
	   par->gradient == gfs_center_minmod_gradient ?
	   "gfs_center_minmod_gradient" :
	   par->gradient == gfs_center_superbee_gradient ?
	   "gfs_center_superbee_gradient" :
	   par->gradient == gfs_center_sweby_gradient ?
	   "gfs_center_sweby_gradient" :
	   "none",
	   par->flux == gfs_face_advection_flux ?
	   "gfs_face_advection_flux" :
	   par->flux == gfs_face_velocity_advection_flux ?
	   "gfs_face_velocity_advection_flux" :
	   par->flux == gfs_face_velocity_convective_flux ?
	   "gfs_face_velocity_convective_flux" : "NULL",
	   par->average);
  if (par->gc)
    fputs ("  gc       = 1\n", fp);
  switch (par->scheme) {
  case GFS_GODUNOV: fputs ("  scheme   = godunov\n", fp); break;
  case GFS_NONE:    fputs ("  scheme   = none\n", fp); break;
  }
  if (par->moving_order != 1)
    fputs ("  moving_order = 2\n", fp);
  if (gts_vector_norm (par->sink) > 0.)
    fprintf (fp, "  vx = %g vy = %g vz = %g\n", par->sink[0], par->sink[1], par->sink[2]);
  if (par->linear)
    fputs ("  linear = 1\n", fp);
  fputc ('}', fp);
}
