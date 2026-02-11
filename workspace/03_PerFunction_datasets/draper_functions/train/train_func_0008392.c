gst_rtp_mpa_robust_depay_class_init (GstRtpMPARobustDepayClass * klass)
{
  GObjectClass *gobject_class;
  GstElementClass *gstelement_class;
  GstRTPBaseDepayloadClass *gstrtpbasedepayload_class;

  GST_DEBUG_CATEGORY_INIT (rtpmparobustdepay_debug, "rtpmparobustdepay", 0,
      "Robust MPEG Audio RTP Depayloader");

  gobject_class = (GObjectClass *) klass;
  gstelement_class = (GstElementClass *) klass;
  gstrtpbasedepayload_class = (GstRTPBaseDepayloadClass *) klass;

  gobject_class->finalize = gst_rtp_mpa_robust_depay_finalize;

  gstelement_class->change_state =
      GST_DEBUG_FUNCPTR (gst_rtp_mpa_robust_change_state);

  gst_element_class_add_pad_template (gstelement_class,
      gst_static_pad_template_get (&gst_rtp_mpa_robust_depay_src_template));
  gst_element_class_add_pad_template (gstelement_class,
      gst_static_pad_template_get (&gst_rtp_mpa_robust_depay_sink_template));

  gst_element_class_set_static_metadata (gstelement_class,
      "RTP MPEG audio depayloader", "Codec/Depayloader/Network/RTP",
      "Extracts MPEG audio from RTP packets (RFC 5219)",
      "Mark Nauwelaerts <mark.nauwelaerts@collabora.co.uk>");

  gstrtpbasedepayload_class->set_caps = gst_rtp_mpa_robust_depay_setcaps;
  gstrtpbasedepayload_class->process = gst_rtp_mpa_robust_depay_process;
}
