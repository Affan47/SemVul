gst_avi_mux_collect_pads (GstCollectPads * pads, GstAviMux * avimux)
{
  GstFlowReturn res;

  if (G_UNLIKELY (avimux->write_header)) {
    if ((res = gst_avi_mux_start_file (avimux)) != GST_FLOW_OK)
      return res;
  }

  return gst_avi_mux_do_one_buffer (avimux);
}
