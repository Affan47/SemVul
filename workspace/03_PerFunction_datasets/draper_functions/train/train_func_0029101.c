gst_app_sink_set_callbacks (GstAppSink * appsink,
    GstAppSinkCallbacks * callbacks, gpointer user_data, GDestroyNotify notify)
{
  GDestroyNotify old_notify;
  GstAppSinkPrivate *priv;

  g_return_if_fail (GST_IS_APP_SINK (appsink));
  g_return_if_fail (callbacks != NULL);

  priv = appsink->priv;

  GST_OBJECT_LOCK (appsink);
  old_notify = priv->notify;

  if (old_notify) {
    gpointer old_data;

    old_data = priv->user_data;

    priv->user_data = NULL;
    priv->notify = NULL;
    GST_OBJECT_UNLOCK (appsink);

    old_notify (old_data);

    GST_OBJECT_LOCK (appsink);
  }
  priv->callbacks = *callbacks;
  priv->user_data = user_data;
  priv->notify = notify;
  priv->buffer_lists_supported =
      gst_app_sink_check_buffer_lists_support (appsink);
  GST_OBJECT_UNLOCK (appsink);
}
