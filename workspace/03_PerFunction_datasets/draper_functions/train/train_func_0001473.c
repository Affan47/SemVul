gst_audio_rate_change_state (GstElement * element, GstStateChange transition)
{
  GstAudioRate *audiorate = GST_AUDIO_RATE (element);

  switch (transition) {
    case GST_STATE_CHANGE_PAUSED_TO_READY:
      break;
    case GST_STATE_CHANGE_READY_TO_PAUSED:
      audiorate->in = 0;
      audiorate->out = 0;
      audiorate->drop = 0;
      audiorate->add = 0;
      gst_audio_info_init (&audiorate->info);
      gst_audio_rate_reset (audiorate);
      break;
    default:
      break;
  }

  return GST_ELEMENT_CLASS (parent_class)->change_state (element, transition);
}
