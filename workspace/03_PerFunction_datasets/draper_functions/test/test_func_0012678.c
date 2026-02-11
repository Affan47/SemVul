ac3iec_change_state (GstElement * element, GstStateChange transition)
{
  AC3IEC *ac3iec;
  GstStateChangeReturn ret;

  g_return_val_if_fail (GST_IS_AC3IEC (element), GST_STATE_CHANGE_FAILURE);

  ac3iec = AC3IEC (element);

  switch (transition) {
    case GST_STATE_CHANGE_NULL_TO_READY:
      break;
    case GST_STATE_CHANGE_READY_TO_PAUSED:
      ac3p_init (ac3iec->padder);
      break;
    case GST_STATE_CHANGE_PAUSED_TO_PLAYING:
      break;
    default:
      break;
  }

  ret = GST_ELEMENT_CLASS (parent_class)->change_state (element, transition);

  switch (transition) {
    case GST_STATE_CHANGE_PLAYING_TO_PAUSED:
      break;
    case GST_STATE_CHANGE_PAUSED_TO_READY:
      ac3p_clear (ac3iec->padder);
      if (ac3iec->caps) {
        gst_caps_unref (ac3iec->caps);
        ac3iec->caps = NULL;
      }
      break;
    case GST_STATE_CHANGE_READY_TO_NULL:
      break;
    default:
      break;
  }

  return ret;
}
