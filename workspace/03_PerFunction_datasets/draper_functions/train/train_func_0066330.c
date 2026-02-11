gst_segment_clip_change_state (GstElement * element, GstStateChange transition)
{
  GstSegmentClip *self = GST_SEGMENT_CLIP (element);
  GstStateChangeReturn ret = GST_STATE_CHANGE_SUCCESS;

  if (GST_ELEMENT_CLASS (parent_class)->change_state)
    ret = GST_ELEMENT_CLASS (parent_class)->change_state (element, transition);

  switch (transition) {
    case GST_STATE_CHANGE_READY_TO_PAUSED:
    case GST_STATE_CHANGE_PAUSED_TO_READY:
      gst_segment_clip_reset (self);
      break;
    default:
      break;
  }

  return ret;
}
