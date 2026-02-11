gst_asf_mux_push_buffer (GstAsfMux * asfmux, GstBuffer * buf)
{
  GstFlowReturn ret;
  gst_buffer_set_caps (buf, GST_PAD_CAPS (asfmux->srcpad));
  ret = gst_pad_push (asfmux->srcpad, buf);
  if (ret == GST_FLOW_OK)
    asfmux->file_size += GST_BUFFER_SIZE (buf);
  return ret;
}
