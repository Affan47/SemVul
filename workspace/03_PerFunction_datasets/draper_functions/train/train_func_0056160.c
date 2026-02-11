tracker_evt_update_items_cb (gpointer              key,
                             gpointer              value,
                             tracker_evt_update_t *evt)
{
  guint id = GPOINTER_TO_INT (key);
  gchar *str_id;
  GrlTrackerSource *source = (GrlTrackerSource *) value;
  GrlMedia *media;

  GRL_DEBUG ("%s: evt=%p", __FUNCTION__, evt);

  if (!source) {
    g_assert ("\tnot in cache ???");
    return;
  }

  if (!grl_tracker_source_can_notify (source)) {
    GRL_DEBUG ("\tno notification for source %s...",
	       grl_source_get_name (GRL_SOURCE (source)));
    return;
  }

  media = grl_media_new ();
  str_id = g_strdup_printf ("%i", id);
  grl_media_set_id (media, str_id);
  g_free (str_id);

  GRL_DEBUG ("\tNotify id=%u source=%s", id,
             grl_source_get_name (GRL_SOURCE (source)));
  grl_source_notify_change (GRL_SOURCE (source), media, evt->change_type, FALSE);

  g_object_unref (media);
}
