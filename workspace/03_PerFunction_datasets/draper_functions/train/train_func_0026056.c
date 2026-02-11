gst_rtspsrc_send_dummy_packets (GstRTSPSrc * src)
{
  GList *walk;

  if (src->nat_method != GST_RTSP_NAT_DUMMY)
    return TRUE;

  for (walk = src->streams; walk; walk = g_list_next (walk)) {
    GstRTSPStream *stream = (GstRTSPStream *) walk->data;

    if (stream->fakesrc && stream->udpsink[0]) {
      GST_DEBUG_OBJECT (src, "sending dummy packet to stream %p", stream);
      gst_element_set_state (stream->udpsink[0], GST_STATE_NULL);
      gst_element_set_state (stream->fakesrc, GST_STATE_NULL);
      gst_element_set_state (stream->udpsink[0], GST_STATE_PLAYING);
      gst_element_set_state (stream->fakesrc, GST_STATE_PLAYING);
    }
  }
  return TRUE;
}
