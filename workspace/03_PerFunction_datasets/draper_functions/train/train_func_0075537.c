gst_compare_change_state (GstElement * element, GstStateChange transition)
{
  GstCompare *comp = GST_COMPARE (element);
  GstStateChangeReturn ret;

  switch (transition) {
    case GST_STATE_CHANGE_NULL_TO_READY:
    case GST_STATE_CHANGE_READY_TO_PAUSED:
      gst_collect_pads_start (comp->cpads);
      break;
    case GST_STATE_CHANGE_PAUSED_TO_READY:
      gst_collect_pads_stop (comp->cpads);
      break;
    default:
      break;
  }

  ret = GST_CALL_PARENT_WITH_DEFAULT (GST_ELEMENT_CLASS, change_state,
      (element, transition), GST_STATE_CHANGE_SUCCESS);
  if (ret != GST_STATE_CHANGE_SUCCESS)
    return ret;

  switch (transition) {
    case GST_STATE_CHANGE_PAUSED_TO_READY:
      gst_compare_reset (comp);
      break;
    default:
      break;
  }

  return GST_STATE_CHANGE_SUCCESS;
}
