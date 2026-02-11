p_gap_set_framerate(gint32 image_id, gdouble framerate)
{
  GimpParam     *l_params;
  gint           l_retvals;

  if (gap_debug)  printf("DEBUG: before p_gap_set_framerate %f\n", (float)framerate);
  l_params = gimp_run_procedure ("plug_in_gap_set_framerate",
                          &l_retvals,
                          GIMP_PDB_INT32,    GIMP_RUN_NONINTERACTIVE,
                          GIMP_PDB_IMAGE,    image_id,
                          GIMP_PDB_DRAWABLE, 0,
                          GIMP_PDB_FLOAT,    framerate,
                          GIMP_PDB_END);

  g_free(l_params);
}
