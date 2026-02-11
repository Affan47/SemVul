ensure_negotiated (GstMonoscope * monoscope)
{
  gboolean reconfigure;

  reconfigure = gst_pad_check_reconfigure (monoscope->srcpad);


  if (reconfigure || !gst_pad_has_current_caps (monoscope->srcpad)) {
    if (!gst_monoscope_src_negotiate (monoscope))
      return GST_FLOW_NOT_NEGOTIATED;
  }
  return GST_FLOW_OK;
}
