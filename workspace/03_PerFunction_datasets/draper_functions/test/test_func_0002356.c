gst_base_transform_drop_delayed_events (GstBaseTransform * trans)
{
  GST_OBJECT_LOCK (trans);
  if (trans->priv->delayed_events) {
    g_list_foreach (trans->priv->delayed_events, (GFunc) gst_event_unref, NULL);
    g_list_free (trans->priv->delayed_events);
    trans->priv->delayed_events = NULL;
  }
  GST_OBJECT_UNLOCK (trans);
}
