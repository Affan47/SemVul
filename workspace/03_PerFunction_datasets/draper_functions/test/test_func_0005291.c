gst_raw_parse_change_state (GstElement * element, GstStateChange transition)
{
  GstRawParse *rp = GST_RAW_PARSE (element);
  GstStateChangeReturn ret = GST_STATE_CHANGE_SUCCESS;

  switch (transition) {
    case GST_STATE_CHANGE_READY_TO_PAUSED:
      gst_segment_init (&rp->segment, GST_FORMAT_TIME);
      rp->segment.position = 0;
    default:
      break;
  }

  if (GST_ELEMENT_CLASS (parent_class)->change_state)
    ret = GST_ELEMENT_CLASS (parent_class)->change_state (element, transition);

  switch (transition) {
    case GST_STATE_CHANGE_PAUSED_TO_READY:
      gst_raw_parse_reset (rp);
      break;
    default:
      break;
  }

  return ret;
}
