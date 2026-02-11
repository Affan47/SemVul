gst_rtp_mp4v_depay_change_state (GstElement * element,
    GstStateChange transition)
{
  GstRtpMP4VDepay *rtpmp4vdepay;
  GstStateChangeReturn ret;

  rtpmp4vdepay = GST_RTP_MP4V_DEPAY (element);

  switch (transition) {
    case GST_STATE_CHANGE_READY_TO_PAUSED:
      gst_adapter_clear (rtpmp4vdepay->adapter);
      break;
    default:
      break;
  }

  ret = GST_ELEMENT_CLASS (parent_class)->change_state (element, transition);

  switch (transition) {
    default:
      break;
  }
  return ret;
}
