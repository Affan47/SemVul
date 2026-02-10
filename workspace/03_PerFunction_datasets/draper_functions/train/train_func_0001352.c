gst_asf_mux_audio_set_caps (GstPad * pad, GstCaps * caps)
{
  GstAsfMux *asfmux;
  GstAsfAudioPad *audiopad;
  GstStructure *structure;
  const gchar *caps_name;
  gint channels, rate;
  gchar *aux;
  const GValue *codec_data;

  asfmux = GST_ASF_MUX (gst_pad_get_parent (pad));

  audiopad = (GstAsfAudioPad *) gst_pad_get_element_private (pad);
  g_assert (audiopad);

  aux = gst_caps_to_string (caps);
  GST_DEBUG_OBJECT (asfmux, "%s:%s, caps=%s", GST_DEBUG_PAD_NAME (pad), aux);
  g_free (aux);

  structure = gst_caps_get_structure (caps, 0);
  caps_name = gst_structure_get_name (structure);

  if (!gst_structure_get_int (structure, "channels", &channels) ||
      !gst_structure_get_int (structure, "rate", &rate))
    goto refuse_caps;

  audiopad->audioinfo.channels = (guint16) channels;
  audiopad->audioinfo.rate = (guint32) rate;


  codec_data = gst_structure_get_value (structure, "codec_data");
  if (codec_data) {
    audiopad->pad.codec_data = gst_value_get_buffer (codec_data);
    gst_buffer_ref (audiopad->pad.codec_data);
  }

  if (strcmp (caps_name, "audio/x-wma") == 0) {
    gint version;
    gint block_align = 0;
    gint bitrate = 0;

    if (!gst_structure_get_int (structure, "wmaversion", &version)) {
      goto refuse_caps;
    }

    if (gst_structure_get_int (structure, "block_align", &block_align)) {
      audiopad->audioinfo.blockalign = (guint16) block_align;
    }
    if (gst_structure_get_int (structure, "bitrate", &bitrate)) {
      audiopad->pad.bitrate = (guint32) bitrate;
      audiopad->audioinfo.av_bps = bitrate / 8;
    }

    if (version == 1) {
      audiopad->audioinfo.format = GST_RIFF_WAVE_FORMAT_WMAV1;
    } else if (version == 2) {
      audiopad->audioinfo.format = GST_RIFF_WAVE_FORMAT_WMAV2;
    } else if (version == 3) {
      audiopad->audioinfo.format = GST_RIFF_WAVE_FORMAT_WMAV3;
    } else {
      goto refuse_caps;
    }
  } else if (strcmp (caps_name, "audio/mpeg") == 0) {
    gint version;
    gint layer;

    if (!gst_structure_get_int (structure, "mpegversion", &version) ||
        !gst_structure_get_int (structure, "layer", &layer)) {
      goto refuse_caps;
    }
    if (version != 1 || layer != 3) {
      goto refuse_caps;
    }

    audiopad->audioinfo.format = GST_RIFF_WAVE_FORMAT_MPEGL3;
  } else {
    goto refuse_caps;
  }

  gst_object_unref (asfmux);
  return TRUE;

refuse_caps:
  GST_WARNING_OBJECT (asfmux, "pad %s refused caps %" GST_PTR_FORMAT,
      GST_PAD_NAME (pad), caps);
  gst_object_unref (asfmux);
  return FALSE;
}
