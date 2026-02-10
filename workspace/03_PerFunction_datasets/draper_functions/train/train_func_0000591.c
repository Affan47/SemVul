gst_rtp_mux_change_state (GstElement * element, GstStateChange transition)
{
  GstRTPMux *rtp_mux;

  rtp_mux = GST_RTP_MUX (element);

  switch (transition) {
    case GST_STATE_CHANGE_NULL_TO_READY:
      break;
    case GST_STATE_CHANGE_READY_TO_PAUSED:
      gst_rtp_mux_ready_to_paused (rtp_mux);
      break;
    case GST_STATE_CHANGE_PAUSED_TO_READY:
      break;
    default:
      break;
  }

  return GST_ELEMENT_CLASS (parent_class)->change_state (element, transition);
}
