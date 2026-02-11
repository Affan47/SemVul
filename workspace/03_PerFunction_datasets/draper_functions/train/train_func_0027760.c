gst_rtp_sbc_depay_class_init (GstRtpSbcDepayClass * klass)
{
  GstRTPBaseDepayloadClass *gstbasertpdepayload_class =
      GST_RTP_BASE_DEPAYLOAD_CLASS (klass);
  GstElementClass *element_class = GST_ELEMENT_CLASS (klass);
  GObjectClass *gobject_class = G_OBJECT_CLASS (klass);

  gobject_class->finalize = gst_rtp_sbc_depay_finalize;

  gstbasertpdepayload_class->set_caps = gst_rtp_sbc_depay_setcaps;
  gstbasertpdepayload_class->process = gst_rtp_sbc_depay_process;

  gst_element_class_add_pad_template (element_class,
      gst_static_pad_template_get (&gst_rtp_sbc_depay_src_template));
  gst_element_class_add_pad_template (element_class,
      gst_static_pad_template_get (&gst_rtp_sbc_depay_sink_template));

  GST_DEBUG_CATEGORY_INIT (rtpsbcdepay_debug, "rtpsbcdepay", 0,
      "SBC Audio RTP Depayloader");

  gst_element_class_set_static_metadata (element_class,
      "RTP SBC audio depayloader",
      "Codec/Depayloader/Network/RTP",
      "Extracts SBC audio from RTP packets",
      "Arun Raghavan <arun.raghavan@collabora.co.uk>");
}
