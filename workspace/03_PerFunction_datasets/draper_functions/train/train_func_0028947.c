gst_auto_convert_change_state (GstElement * element, GstStateChange transition)
{
  GstAutoConvert *autoconvert = GST_AUTO_CONVERT (element);
  GstStateChangeReturn ret;

  switch (transition) {
    default:
      break;
  }

  ret = GST_ELEMENT_CLASS (parent_class)->change_state (element, transition);
  if (ret == GST_STATE_CHANGE_FAILURE)
    return ret;

  switch (transition) {
    case GST_STATE_CHANGE_PAUSED_TO_READY:
      g_list_foreach (autoconvert->cached_events, (GFunc) gst_mini_object_unref,
          NULL);
      g_list_free (autoconvert->cached_events);
      autoconvert->cached_events = NULL;
      break;
    default:
      break;
  }

  return ret;
}
