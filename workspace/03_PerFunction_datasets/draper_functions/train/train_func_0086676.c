gst_aasink_change_state (GstElement * element, GstStateChange transition)
{
  GstStateChangeReturn ret;


  switch (transition) {
    case GST_STATE_CHANGE_NULL_TO_READY:
      break;
    case GST_STATE_CHANGE_READY_TO_PAUSED:
      if (!gst_aasink_open (GST_AASINK (element)))
        goto open_failed;
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
      break;
    case GST_STATE_CHANGE_READY_TO_NULL:
      gst_aasink_close (GST_AASINK (element));
      break;
    default:
      break;
  }

  return ret;

open_failed:
  {
    return GST_STATE_CHANGE_FAILURE;
  }
}
