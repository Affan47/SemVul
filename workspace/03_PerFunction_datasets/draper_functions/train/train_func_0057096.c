gst_smpte_change_state (GstElement * element, GstStateChange transition)
{
  GstStateChangeReturn ret;
  GstSMPTE *smpte;

  smpte = GST_SMPTE (element);

  switch (transition) {
    case GST_STATE_CHANGE_READY_TO_PAUSED:
      gst_smpte_reset (smpte);
      GST_LOG_OBJECT (smpte, "starting collectpads");
      gst_collect_pads_start (smpte->collect);
      break;
    case GST_STATE_CHANGE_PAUSED_TO_READY:
      GST_LOG_OBJECT (smpte, "stopping collectpads");
      gst_collect_pads_stop (smpte->collect);
      break;
    default:
      break;
  }

  ret = GST_ELEMENT_CLASS (parent_class)->change_state (element, transition);

  switch (transition) {
    case GST_STATE_CHANGE_PAUSED_TO_READY:
      gst_smpte_reset (smpte);
      break;
    default:
      break;
  }
  return ret;
}
