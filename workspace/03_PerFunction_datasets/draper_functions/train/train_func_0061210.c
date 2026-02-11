gst_text_overlay_change_state (GstElement * element, GstStateChange transition)
{
  GstStateChangeReturn ret = GST_STATE_CHANGE_SUCCESS;
  GstCairoTextOverlay *overlay = GST_CAIRO_TEXT_OVERLAY (element);

  switch (transition) {
    case GST_STATE_CHANGE_READY_TO_PAUSED:
      gst_collect_pads_start (overlay->collect);
      break;
    case GST_STATE_CHANGE_PAUSED_TO_READY:


      gst_collect_pads_stop (overlay->collect);
      break;
    default:
      break;
  }

  ret = parent_class->change_state (element, transition);
  if (ret == GST_STATE_CHANGE_FAILURE)
    return ret;

  switch (transition) {
    default:
      break;
  }

  return ret;
}
