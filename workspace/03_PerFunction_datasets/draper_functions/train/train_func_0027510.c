gst_rtp_jpeg_pay_class_init (GstRtpJPEGPayClass * klass)
{
  GObjectClass *gobject_class;
  GstBaseRTPPayloadClass *gstbasertppayload_class;

  gobject_class = (GObjectClass *) klass;
  gstbasertppayload_class = (GstBaseRTPPayloadClass *) klass;

  gobject_class->set_property = gst_rtp_jpeg_pay_set_property;
  gobject_class->get_property = gst_rtp_jpeg_pay_get_property;

  gstbasertppayload_class->set_caps = gst_rtp_jpeg_pay_setcaps;
  gstbasertppayload_class->handle_buffer = gst_rtp_jpeg_pay_handle_buffer;

  g_object_class_install_property (G_OBJECT_CLASS (klass), PROP_JPEG_QUALITY,
      g_param_spec_int ("quality", "Quality",
          "Quality factor on JPEG data (unused)", 0, 255, 255,
          G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS));

  g_object_class_install_property (G_OBJECT_CLASS (klass), PROP_JPEG_TYPE,
      g_param_spec_int ("type", "Type",
          "Default JPEG Type, overwritten by SOF when present", 0, 255,
          DEFAULT_JPEG_TYPE, G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS));

  g_object_class_install_property (G_OBJECT_CLASS (klass), PROP_BUFFER_LIST,
      g_param_spec_boolean ("buffer-list", "Buffer List",
          "Use Buffer Lists",
          DEFAULT_BUFFER_LIST, G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS));

  GST_DEBUG_CATEGORY_INIT (rtpjpegpay_debug, "rtpjpegpay", 0,
      "Motion JPEG RTP Payloader");
}
