gst_base_audio_visualizer_sink_setcaps (GstPad * pad, GstCaps * caps)
{
  GstBaseAudioVisualizer *scope;
  GstStructure *structure;
  gint channels;
  gint rate;
  gboolean res = TRUE;

  scope = GST_BASE_AUDIO_VISUALIZER (gst_pad_get_parent (pad));
  structure = gst_caps_get_structure (caps, 0);

  if (!gst_structure_get_int (structure, "channels", &channels) ||
      !gst_structure_get_int (structure, "rate", &rate))
    goto missing_caps_details;

  if (channels != 2)
    goto wrong_channels;

  if (rate <= 0)
    goto wrong_rate;

  scope->channels = channels;
  scope->rate = rate;

  GST_DEBUG_OBJECT (scope, "audio: channels %d, rate %d",
      scope->channels, scope->rate);

done:
  gst_object_unref (scope);
  return res;


missing_caps_details:
  {
    GST_WARNING_OBJECT (scope, "missing channels or rate in the caps");
    res = FALSE;
    goto done;
  }
wrong_channels:
  {
    GST_WARNING_OBJECT (scope, "number of channels must be 2, but is %d",
        channels);
    res = FALSE;
    goto done;
  }
wrong_rate:
  {
    GST_WARNING_OBJECT (scope, "sample rate must be >0, but is %d", rate);
    res = FALSE;
    goto done;
  }
}
