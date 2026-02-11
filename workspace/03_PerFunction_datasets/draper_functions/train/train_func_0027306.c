gst_rtp_opus_depay_setcaps (GstRTPBaseDepayload * depayload, GstCaps * caps)
{
  GstCaps *srccaps;
  gboolean ret;

  srccaps = gst_caps_new_empty_simple ("audio/x-opus");
  ret = gst_pad_set_caps (GST_RTP_BASE_DEPAYLOAD_SRCPAD (depayload), srccaps);

  GST_DEBUG_OBJECT (depayload,
      "set caps on source: %" GST_PTR_FORMAT " (ret=%d)", srccaps, ret);
  gst_caps_unref (srccaps);

  depayload->clock_rate = 48000;

  return ret;
}
