gst_rtp_vraw_depay_change_state (GstElement * element,
    GstStateChange transition)
{
  GstRtpVRawDepay *rtpvrawdepay;
  GstStateChangeReturn ret;

  rtpvrawdepay = GST_RTP_VRAW_DEPAY (element);

  switch (transition) {
    case GST_STATE_CHANGE_NULL_TO_READY:
      break;
    case GST_STATE_CHANGE_READY_TO_PAUSED:
      gst_rtp_vraw_depay_reset (rtpvrawdepay);
      break;
    default:
      break;
  }

  ret = GST_ELEMENT_CLASS (parent_class)->change_state (element, transition);

  switch (transition) {
    case GST_STATE_CHANGE_PAUSED_TO_READY:
      gst_rtp_vraw_depay_reset (rtpvrawdepay);
      break;
    case GST_STATE_CHANGE_READY_TO_NULL:
      break;
    default:
      break;
  }
  return ret;
}
