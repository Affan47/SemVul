mpegts_parse_change_state (GstElement * element, GstStateChange transition)
{
  MpegTSParse *parse;
  GstStateChangeReturn ret;

  parse = GST_MPEGTS_PARSE (element);
  ret = GST_ELEMENT_CLASS (parent_class)->change_state (element, transition);

  switch (transition) {
    case GST_STATE_CHANGE_PAUSED_TO_READY:
      mpegts_parse_reset (parse);
      break;
    default:
      break;
  }

  return ret;
}
