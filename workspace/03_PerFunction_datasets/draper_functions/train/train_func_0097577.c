radial_center_set_cb (ggobid *gg, gint index,
  gint state, GGobiData *d, PluginInstance *inst)
{
  glayoutd *gl = glayoutFromInst (inst);
  GtkWidget *entry;

  if (gl == NULL || gl->window == NULL)
    return;

  entry = (GtkWidget *) g_object_get_data(G_OBJECT(gl->window),
    "CENTERNODE");
  if (entry == NULL)
    return;

  if (state == STICKY && index >= 0) {

    gint i, k, nsticky = g_slist_length (d->sticky_ids);
    for (i = 0; i<nsticky-1; i++) {
      k = (gint) g_slist_nth_data (d->sticky_ids, 0);
      d->sticky_ids = g_slist_remove (d->sticky_ids,
				      g_slist_nth_data (d->sticky_ids, 0));
      sticky_id_link_by_id (STICKY_REMOVE, k, d, gg);
      g_signal_emit(G_OBJECT(gg),
        getGGobiSignal(STICKY_POINT_REMOVED_SIGNAL), 0,
        (gint) UNSTICKY, d);
    }

    gtk_entry_set_text (GTK_ENTRY (entry),
      (gchar *) g_array_index (d->rowlab, gchar *, index));
    gl->centerNodeIndex = index;

    if (gl->radialAutoUpdate) {
       do_radial(gl, gl->dsrc, gl->e, gg->current_display, gg);
    }
  }
}
