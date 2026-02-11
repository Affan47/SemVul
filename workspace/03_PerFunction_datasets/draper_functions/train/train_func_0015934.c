gst_rtp_jpeg_pay_set_property (GObject * object, guint prop_id,
    const GValue * value, GParamSpec * pspec)
{
  GstRtpJPEGPay *rtpjpegpay;

  rtpjpegpay = GST_RTP_JPEG_PAY (object);

  switch (prop_id) {
    case PROP_JPEG_QUALITY:
      rtpjpegpay->quality = g_value_get_int (value);
      GST_DEBUG_OBJECT (object, "quality = %d", rtpjpegpay->quality);
      break;
    case PROP_JPEG_TYPE:
      rtpjpegpay->type = g_value_get_int (value);
      GST_DEBUG_OBJECT (object, "type = %d", rtpjpegpay->type);
      break;
    case PROP_BUFFER_LIST:
      rtpjpegpay->buffer_list = g_value_get_boolean (value);
      GST_DEBUG_OBJECT (object, "buffer_list = %d", rtpjpegpay->buffer_list);
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
  }
}
