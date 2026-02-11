gst_audio_decoder_change_state (GstElement * element, GstStateChange transition)
{
  GstAudioDecoder *codec;
  GstStateChangeReturn ret;

  codec = GST_AUDIO_DECODER (element);

  switch (transition) {
    case GST_STATE_CHANGE_NULL_TO_READY:
      break;
    case GST_STATE_CHANGE_READY_TO_PAUSED:
      if (!gst_audio_decoder_start (codec)) {
        goto start_failed;
      }
      break;
    case GST_STATE_CHANGE_PAUSED_TO_PLAYING:
      break;
    default:
      break;
  }

  ret = parent_class->change_state (element, transition);

  switch (transition) {
    case GST_STATE_CHANGE_PLAYING_TO_PAUSED:
      break;
    case GST_STATE_CHANGE_PAUSED_TO_READY:
      if (!gst_audio_decoder_stop (codec)) {
        goto stop_failed;
      }
      break;
    case GST_STATE_CHANGE_READY_TO_NULL:
      break;
    default:
      break;
  }

  return ret;

start_failed:
  {
    GST_ELEMENT_ERROR (codec, LIBRARY, INIT, (NULL), ("Failed to start codec"));
    return GST_STATE_CHANGE_FAILURE;
  }
stop_failed:
  {
    GST_ELEMENT_ERROR (codec, LIBRARY, INIT, (NULL), ("Failed to stop codec"));
    return GST_STATE_CHANGE_FAILURE;
  }
}
