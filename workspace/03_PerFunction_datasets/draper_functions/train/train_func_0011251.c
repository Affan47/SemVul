gst_curl_base_sink_wait_for_transfer_thread_to_send_unlocked
    (GstCurlBaseSink * sink)
{
  GST_LOG ("waiting for buffer send to complete");


  while (!sink->transfer_cond->data_sent) {
    g_cond_wait (&sink->transfer_cond->cond, GST_OBJECT_GET_LOCK (sink));
  }
  GST_LOG ("buffer send completed");
}
