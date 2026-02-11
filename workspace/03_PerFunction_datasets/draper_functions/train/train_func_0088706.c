gst_pngdec_change_state (GstElement * element, GstStateChange transition)
{
  GstStateChangeReturn ret;
  GstPngDec *pngdec;

  pngdec = GST_PNGDEC (element);

  switch (transition) {
    case GST_STATE_CHANGE_READY_TO_PAUSED:
      gst_pngdec_libpng_init (pngdec);
      pngdec->need_newsegment = TRUE;
      pngdec->framed = FALSE;
      pngdec->ret = GST_FLOW_OK;
      gst_segment_init (&pngdec->segment, GST_FORMAT_UNDEFINED);
      break;
    default:
      break;
  }

  ret = parent_class->change_state (element, transition);
  if (ret != GST_STATE_CHANGE_SUCCESS)
    return ret;

  switch (transition) {
    case GST_STATE_CHANGE_PAUSED_TO_READY:
      gst_pngdec_libpng_clear (pngdec);
      break;
    default:
      break;
  }

  return ret;
}
