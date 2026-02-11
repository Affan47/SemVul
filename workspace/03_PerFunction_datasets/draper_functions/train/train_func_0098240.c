gst_smart_encoder_change_state (GstElement * element, GstStateChange transition)
{
  GstSmartEncoder *smart_encoder;
  GstStateChangeReturn ret;

  g_return_val_if_fail (GST_IS_SMART_ENCODER (element),
      GST_STATE_CHANGE_FAILURE);

  smart_encoder = GST_SMART_ENCODER (element);

  switch (transition) {
    case GST_STATE_CHANGE_NULL_TO_READY:

      if ((ret =
              gst_smart_encoder_find_elements (smart_encoder)) ==
          GST_STATE_CHANGE_FAILURE)
        goto beach;
      break;
    default:
      break;
  }

  ret =
      GST_ELEMENT_CLASS (gst_smart_encoder_parent_class)->change_state (element,
      transition);

  switch (transition) {
    case GST_STATE_CHANGE_PAUSED_TO_READY:
      smart_encoder_reset (smart_encoder);
      break;
    default:
      break;
  }

beach:
  return ret;
}
