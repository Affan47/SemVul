gst_real_video_dec_change_state (GstElement * element,
    GstStateChange transition)
{
  GstStateChangeReturn ret;
  GstRealVideoDec *dec = GST_REAL_VIDEO_DEC (element);

  switch (transition) {
    case GST_STATE_CHANGE_NULL_TO_READY:
      gst_real_video_dec_probe_modules (dec);
      dec->checked_modules = TRUE;
      break;
    default:
      break;
  }

  ret = GST_ELEMENT_CLASS (parent_class)->change_state (element, transition);

  switch (transition) {
    case GST_STATE_CHANGE_PAUSED_TO_READY:
      close_library (dec, &dec->lib);
      break;
    case GST_STATE_CHANGE_READY_TO_NULL:
      dec->checked_modules = FALSE;
      break;
    default:
      break;
  }
  return ret;
}
