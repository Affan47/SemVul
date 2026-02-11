new_packet_cb (guint8 * data, guint len, void *user_data)
{


  MpegPsMux *mux = (MpegPsMux *) user_data;
  GstBuffer *buf;
  GstFlowReturn ret;

  GST_LOG_OBJECT (mux, "Outputting a packet of length %d", len);

  data = g_memdup (data, len);
  buf = gst_buffer_new_wrapped (data, len);

  GST_BUFFER_TIMESTAMP (buf) = mux->last_ts;

  if (mux->aggregate_gops) {
    if (mux->gop_list == NULL)
      mux->gop_list = gst_buffer_list_new ();

    gst_buffer_list_add (mux->gop_list, buf);
    return TRUE;
  }

  ret = gst_pad_push (mux->srcpad, buf);

  if (G_UNLIKELY (ret != GST_FLOW_OK)) {
    mux->last_flow_ret = ret;
    return FALSE;
  }

  return TRUE;
}
