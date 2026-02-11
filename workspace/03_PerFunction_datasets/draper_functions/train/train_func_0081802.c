gst_play_sink_audio_convert_add_conversion_elements (GstPlaySinkAudioConvert *
    self)
{
  GstPlaySinkConvertBin *cbin = GST_PLAY_SINK_CONVERT_BIN (self);
  GstElement *el, *prev = NULL;

  g_assert (cbin->conversion_elements == NULL);

  GST_DEBUG_OBJECT (self,
      "Building audio conversion with use-converters %d, use-volume %d",
      self->use_converters, self->use_volume);

  if (self->use_converters) {
    el = gst_play_sink_convert_bin_add_conversion_element_factory (cbin,
        "audioconvert", "conv");
    if (el) {
      prev = el;
    }

    el = gst_play_sink_convert_bin_add_conversion_element_factory (cbin,
        "audioresample", "resample");
    if (el) {

      if (prev) {
        if (!gst_element_link_pads_full (prev, "src", el, "sink",
                GST_PAD_LINK_CHECK_TEMPLATE_CAPS))
          goto link_failed;
      }
      prev = el;
    }
  }

  if (self->use_volume && self->volume) {
    el = self->volume;
    gst_play_sink_convert_bin_add_conversion_element (cbin, el);
    if (prev) {
      if (!gst_element_link_pads_full (prev, "src", el, "sink",
              GST_PAD_LINK_CHECK_TEMPLATE_CAPS))
        goto link_failed;
    }
    prev = el;
  }

  return TRUE;

link_failed:
  return FALSE;
}
