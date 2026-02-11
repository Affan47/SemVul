gst_curl_sink_event (GstBaseSink * bsink, GstEvent * event)
{
  GstCurlSink *sink = GST_CURL_SINK (bsink);

  switch (event->type) {
    case GST_EVENT_EOS:
      GST_DEBUG_OBJECT (sink, "received EOS");
      GST_OBJECT_LOCK (sink);
      gst_curl_sink_transfer_thread_close_unlocked (sink);
      GST_OBJECT_UNLOCK (sink);
      if (sink->transfer_thread != NULL) {
        g_thread_join (sink->transfer_thread);
        sink->transfer_thread = NULL;
      }
      break;
    default:
      break;
  }
  return TRUE;
}
