gfs_simulation_read (GtsFile * fp)
{
  GfsDomain * d;
  GSList * ml = NULL;

  g_return_val_if_fail (fp != NULL, NULL);

  while (fp->type == '\n')
     gts_file_next_token (fp);

  while (fp->type == GTS_STRING && !strcmp (fp->token->str, "GModule")) {
    GModule * module = load_module (fp, NULL);
    if (module == NULL)
      return NULL;
    ml = g_slist_prepend (ml, module);
    while (fp->type == '\n')
      gts_file_next_token (fp);
  }

  d = gfs_domain_read (fp);
  if (d != NULL && !GFS_IS_SIMULATION (d)) {
    gts_file_error (fp, "parent graph is not a GfsSimulation");
    gts_object_destroy (GTS_OBJECT (d));
    g_slist_free (ml);
    return NULL;
  }
  if (d)
    GFS_SIMULATION (d)->preloaded_modules = g_slist_reverse (ml);
  else
    g_slist_free (ml);
  return GFS_SIMULATION (d);
}
