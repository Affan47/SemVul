gst_real_audio_demux_change_state (GstElement * element,
    GstStateChange transition)
{
  GstStateChangeReturn ret = GST_STATE_CHANGE_SUCCESS;
  GstRealAudioDemux *demux = GST_REAL_AUDIO_DEMUX (element);

  switch (transition) {
    case GST_STATE_CHANGE_NULL_TO_READY:
      break;
    case GST_STATE_CHANGE_READY_TO_PAUSED:
      demux->state = REAL_AUDIO_DEMUX_STATE_MARKER;
      demux->segment_running = FALSE;
      gst_segment_init (&demux->segment, GST_FORMAT_TIME);
      gst_adapter_clear (demux->adapter);
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
    case GST_STATE_CHANGE_PAUSED_TO_READY:{
      gst_real_audio_demux_reset (demux);
      gst_segment_init (&demux->segment, GST_FORMAT_UNDEFINED);
      break;
    }
    case GST_STATE_CHANGE_READY_TO_NULL:
      break;
    default:
      break;
  }

  return ret;
}
