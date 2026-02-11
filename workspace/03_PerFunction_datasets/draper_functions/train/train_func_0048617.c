potential_stats_event (GfsEvent * event, GfsSimulation * sim)
{
  if ((* GFS_EVENT_CLASS (gfs_output_class())->event) (event, sim)) {
    GfsElectroHydro * elec = GFS_ELECTRO_HYDRO (sim);
    FILE * fp = GFS_OUTPUT (event)->file->fp;

    if (elec->electric_projection_params.niter > 0) {
      fprintf (fp, "Electric potential    before     after       rate\n");
      gfs_multilevel_params_stats_write (&elec->electric_projection_params, fp);
    }
    return TRUE;
  }
  return FALSE;
}
