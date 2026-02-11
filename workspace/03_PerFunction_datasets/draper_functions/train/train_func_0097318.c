diffusion_stats_event (GfsEvent * event, GfsSimulation * sim)
{
  if ((* GFS_EVENT_CLASS (gfs_output_class())->event) (event, sim)) {
    FILE * fp = GFS_OUTPUT (event)->file->fp;
    GSList * l = NULL, * i;

    i = GFS_DOMAIN (sim)->variables;
    while (i) {
      GfsVariable * v = i->data;

      if (v->sources) {
	GSList * j = GTS_SLIST_CONTAINER (v->sources)->items;

	while (j) {
	  GtsObject * o = j->data;

	  if (GFS_IS_SOURCE_DIFFUSION (o) && GFS_SOURCE_DIFFUSION (o)->D->par.niter > 0 &&
	      !g_slist_find (l, o)) {
	    l = g_slist_prepend (l, o);
	    fprintf (fp, "%s diffusion\n", v->name);
	    gfs_multilevel_params_stats_write (&GFS_SOURCE_DIFFUSION (o)->D->par, fp);
	  }
	  j = j->next;
	}
      }
      i = i->next;
    }
    g_slist_free (l);
    return TRUE;
  }
  return FALSE;
}
