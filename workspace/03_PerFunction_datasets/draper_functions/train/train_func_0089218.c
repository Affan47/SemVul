gst_soup_http_client_sink_event (GstBaseSink * sink, GstEvent * event)
{
  GstSoupHttpClientSink *souphttpsink = GST_SOUP_HTTP_CLIENT_SINK (sink);

  GST_DEBUG_OBJECT (souphttpsink, "event");

  if (GST_EVENT_TYPE (event) == GST_EVENT_EOS) {
    GST_DEBUG_OBJECT (souphttpsink, "got eos");
    g_mutex_lock (souphttpsink->mutex);
    while (souphttpsink->message) {
      GST_DEBUG_OBJECT (souphttpsink, "waiting");
      g_cond_wait (souphttpsink->cond, souphttpsink->mutex);
    }
    g_mutex_unlock (souphttpsink->mutex);
    GST_DEBUG_OBJECT (souphttpsink, "finished eos");
  }

  return TRUE;
}
