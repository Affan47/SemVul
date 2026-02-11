gst_rtp_h264_depay_handle_event (GstBaseRTPDepayload * depay, GstEvent * event)
{
  GstRtpH264Depay *rtph264depay;

  rtph264depay = GST_RTP_H264_DEPAY (depay);

  switch (GST_EVENT_TYPE (event)) {
    case GST_EVENT_FLUSH_STOP:
      gst_rtp_h264_depay_reset (rtph264depay);
      break;
    default:
      break;
  }

  return
      GST_BASE_RTP_DEPAYLOAD_CLASS (parent_class)->handle_event (depay, event);
}
