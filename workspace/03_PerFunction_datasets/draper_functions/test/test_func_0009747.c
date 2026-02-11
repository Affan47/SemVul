gst_audio_visualizer_sink_setcaps (GstAudioVisualizer * scope, GstCaps * caps)
{
  GstAudioInfo info;

  if (!gst_audio_info_from_caps (&info, caps))
    goto wrong_caps;

  scope->ainfo = info;

  GST_DEBUG_OBJECT (scope, "audio: channels %d, rate %d",
      GST_AUDIO_INFO_CHANNELS (&info), GST_AUDIO_INFO_RATE (&info));

  if (!gst_audio_visualizer_src_negotiate (scope)) {
    goto not_negotiated;
  }

  return TRUE;


wrong_caps:
  {
    GST_WARNING_OBJECT (scope, "could not parse caps");
    return FALSE;
  }
not_negotiated:
  {
    GST_WARNING_OBJECT (scope, "failed to negotiate");
    return FALSE;
  }
}
