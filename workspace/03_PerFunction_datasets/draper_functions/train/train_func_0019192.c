tracker_evt_update_source_del (tracker_evt_update_t *evt,
                               GrlTrackerSource *source)
{
  GrlTrackerSourcePriv *priv = GRL_TRACKER_SOURCE_GET_PRIVATE (source);

  priv->notification_ref++;
  priv->state = GRL_TRACKER_SOURCE_STATE_DELETING;

  evt->old_sources = g_list_append (evt->old_sources, source);

  GRL_DEBUG ("Predel source p=%p name=%s id=%s count=%u", source,
             grl_source_get_name (GRL_SOURCE (source)),
             grl_tracker_source_get_tracker_source (source),
             priv->notification_ref);
}
