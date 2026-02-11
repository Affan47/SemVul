gst_curl_base_sink_got_response_notify (GstCurlBaseSink * sink)
{
  GST_LOG ("got response code");

  GST_OBJECT_LOCK (sink);
  sink->transfer_cond->wait_for_response = FALSE;
  g_cond_signal (&sink->transfer_cond->cond);
  GST_OBJECT_UNLOCK (sink);
}
