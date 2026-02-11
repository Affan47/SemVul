gfs_init_stokes_wave_write (GtsObject * o, FILE * fp)
{
  if (GTS_OBJECT_CLASS (gfs_init_stokes_wave_class ())->parent_class->write)
    (* GTS_OBJECT_CLASS (gfs_init_stokes_wave_class ())->parent_class->write)
      (o, fp);

  fprintf (fp, " { depth = %g steepness = %g }\n",
	   GFS_INIT_STOKES_WAVE (o)->depth,
	   GFS_INIT_STOKES_WAVE (o)->steepness);
}
