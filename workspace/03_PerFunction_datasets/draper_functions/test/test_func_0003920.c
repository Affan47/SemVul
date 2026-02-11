gst_mss_demux_change_state (GstElement * element, GstStateChange transition)
{
  GstMssDemux *mssdemux = GST_MSS_DEMUX_CAST (element);
  GstStateChangeReturn result = GST_STATE_CHANGE_FAILURE;

  switch (transition) {
    case GST_STATE_CHANGE_PAUSED_TO_READY:
      gst_mss_demux_reset (mssdemux);
      break;
    case GST_STATE_CHANGE_READY_TO_NULL:
      break;
    default:
      break;
  }

  result = GST_ELEMENT_CLASS (parent_class)->change_state (element, transition);

  switch (transition) {
    case GST_STATE_CHANGE_READY_TO_PAUSED:{
      gst_segment_init (&mssdemux->segment, GST_FORMAT_TIME);
      break;
    }
    default:
      break;
  }

  return result;
}
