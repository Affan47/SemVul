gst_rtp_sbc_pay_class_init (GstRtpSBCPayClass * klass)
{
  GstRTPBasePayloadClass *payload_class = GST_RTP_BASE_PAYLOAD_CLASS (klass);
  GstElementClass *element_class = GST_ELEMENT_CLASS (klass);
  GObjectClass *gobject_class = G_OBJECT_CLASS (klass);

  gobject_class->finalize = gst_rtp_sbc_pay_finalize;
  gobject_class->set_property = gst_rtp_sbc_pay_set_property;
  gobject_class->get_property = gst_rtp_sbc_pay_get_property;

  payload_class->set_caps = GST_DEBUG_FUNCPTR (gst_rtp_sbc_pay_set_caps);
  payload_class->handle_buffer =
      GST_DEBUG_FUNCPTR (gst_rtp_sbc_pay_handle_buffer);
  payload_class->sink_event = GST_DEBUG_FUNCPTR (gst_rtp_sbc_pay_sink_event);


  g_object_class_install_property (G_OBJECT_CLASS (klass),
      PROP_MIN_FRAMES,
      g_param_spec_int ("min-frames", "minimum frame number",
          "Minimum quantity of frames to send in one packet "
          "(-1 for maximum allowed by the mtu)",
          -1, G_MAXINT, DEFAULT_MIN_FRAMES, G_PARAM_READWRITE));

  gst_element_class_add_pad_template (element_class,
      gst_static_pad_template_get (&gst_rtp_sbc_pay_sink_factory));
  gst_element_class_add_pad_template (element_class,
      gst_static_pad_template_get (&gst_rtp_sbc_pay_src_factory));

  gst_element_class_set_static_metadata (element_class, "RTP packet payloader",
      "Codec/Payloader/Network", "Payload SBC audio as RTP packets",
      "Thiago Sousa Santos <thiagoss@lcc.ufcg.edu.br>");

  GST_DEBUG_CATEGORY_INIT (gst_rtp_sbc_pay_debug, "rtpsbcpay", 0,
      "RTP SBC payloader");
}
