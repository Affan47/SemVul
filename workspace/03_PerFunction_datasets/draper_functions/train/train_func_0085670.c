tracker_evt_update_source_add (tracker_evt_update_t *evt,
                               const gchar *id,
                               const gchar *source_name)
{
  GrlTrackerSource *source;
  GrlTrackerSourcePriv *priv;

  source = g_hash_table_lookup (grl_tracker_source_sources_modified, id);
  if (!source) {
    source = g_object_new (GRL_TRACKER_SOURCE_TYPE,
			   "source-id", id,
			   "source-name", source_name,
			   "source-desc", GRL_TRACKER_SOURCE_DESC,
			   "tracker-connection", grl_tracker_connection,
                           "tracker-datasource", id,
			   NULL);
    g_hash_table_insert (grl_tracker_source_sources_modified,
                         (gpointer) grl_tracker_source_get_tracker_source (source),
                        source);
  }

  priv = GRL_TRACKER_SOURCE_GET_PRIVATE (source);
  priv->state = GRL_TRACKER_SOURCE_STATE_INSERTING;
  priv->notification_ref++;

  evt->new_sources = g_list_append (evt->new_sources, source);

  GRL_DEBUG ("Preadd source p=%p name=%s id=%s count=%u",
             source, source_name, id, priv->notification_ref);
}
