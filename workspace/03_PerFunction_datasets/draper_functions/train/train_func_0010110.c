gst_app_sink_setcaps (GstBaseSink * sink, GstCaps * caps)
{
  GstAppSink *appsink = GST_APP_SINK_CAST (sink);
  GstAppSinkPrivate *priv = appsink->priv;

  g_mutex_lock (&priv->mutex);
  GST_DEBUG_OBJECT (appsink, "receiving CAPS");
  g_queue_push_tail (priv->queue, gst_event_new_caps (caps));
  gst_caps_replace (&priv->preroll_caps, caps);
  g_mutex_unlock (&priv->mutex);

  return TRUE;
}
