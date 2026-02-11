gst_rtp_h263_depay_change_state (GstElement * element,
    GstStateChange transition)
{
  GstRtpH263Depay *rtph263depay;
  GstStateChangeReturn ret;

  rtph263depay = GST_RTP_H263_DEPAY (element);

  switch (transition) {
    case GST_STATE_CHANGE_NULL_TO_READY:
      break;
    case GST_STATE_CHANGE_READY_TO_PAUSED:
      gst_adapter_clear (rtph263depay->adapter);
      rtph263depay->start = TRUE;
      break;
    default:
      break;
  }

  ret = GST_ELEMENT_CLASS (parent_class)->change_state (element, transition);

  switch (transition) {
    case GST_STATE_CHANGE_READY_TO_NULL:
      break;
    default:
      break;
  }
  return ret;
}
