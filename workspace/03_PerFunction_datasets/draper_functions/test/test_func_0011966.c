gfs_output_povray_density_event (GfsEvent * event,
						 GfsSimulation * sim)
{
  if ((* GFS_EVENT_CLASS (GTS_OBJECT_CLASS
			  (gfs_output_povray_DF3_class ())->parent_class)->event)
      (event, sim)) {
    GfsOutputScalar *output = GFS_OUTPUT_SCALAR (event);
    GfsDomain *domain = GFS_DOMAIN (sim);

    gfs_write_povray_density (domain,
			      output->condition,
			      output->v, output->min, output->max,
			      FTT_TRAVERSE_LEAFS, output->maxlevel,
			      GFS_OUTPUT (event)->file->fp);

    fflush (GFS_OUTPUT (event)->file->fp);
    return TRUE;
  }
  return FALSE;
}
