wave_init (GfsWave * wave)
{
  wave->nk = 25;
  wave->ntheta = 24;
  wave->alpha_s = 0.;


  GFS_SIMULATION (wave)->physical_params.g = 9.81/1000.*3600.;

  GfsAdvectionParams * par = &GFS_SIMULATION (wave)->advection_params;
  par->gradient = gfs_center_van_leer_gradient;
  par->flux = gfs_face_advection_flux;
  par->use_centered_velocity = FALSE;

  static GfsDerivedVariableInfo derived_variable[] = {
    { "Hs", "Significant wave height", cell_hs },
    { "Energy", "Wave energy", cell_E },
    { "Frequency", "Wave frequency", cell_frequency },
    { "Direction", "Wave direction (angle)", cell_direction },
    { NULL, NULL, NULL}
  };
  GfsDerivedVariableInfo * v = derived_variable;
  while (v->name) {
    g_assert (gfs_domain_add_derived_variable (GFS_DOMAIN (wave), *v));
    v++;
  }
}
