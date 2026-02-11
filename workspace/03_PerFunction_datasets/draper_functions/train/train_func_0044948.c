gst_dvdlpcmdec_setcaps (GstPad * pad, GstCaps * caps)
{
  GstStructure *structure;
  gboolean res = TRUE;
  GstDvdLpcmDec *dvdlpcmdec;
  GstAudioFormat format;
  gint rate, channels, width;
  const GstAudioChannelPosition *position;

  g_return_val_if_fail (caps != NULL, FALSE);
  g_return_val_if_fail (pad != NULL, FALSE);

  dvdlpcmdec = GST_DVDLPCMDEC (gst_pad_get_parent (pad));

  structure = gst_caps_get_structure (caps, 0);


  if (gst_structure_has_name (structure, "audio/x-private1-lpcm")) {
    gst_pad_set_chain_function (dvdlpcmdec->sinkpad, gst_dvdlpcmdec_chain_dvd);
    goto done;
  }

  gst_pad_set_chain_function (dvdlpcmdec->sinkpad, gst_dvdlpcmdec_chain_raw);

  res &= gst_structure_get_int (structure, "rate", &rate);
  res &= gst_structure_get_int (structure, "channels", &channels);
  res &= gst_structure_get_int (structure, "width", &width);
  res &= gst_structure_get_int (structure, "dynamic_range",
      &dvdlpcmdec->dynamic_range);
  res &= gst_structure_get_boolean (structure, "emphasis",
      &dvdlpcmdec->emphasis);
  res &= gst_structure_get_boolean (structure, "mute", &dvdlpcmdec->mute);

  if (!res)
    goto caps_parse_error;

  switch (width) {
    case 24:
    case 20:
      format = GST_AUDIO_FORMAT_S24BE;
      break;
    case 16:
      format = GST_AUDIO_FORMAT_S16BE;
      break;
    default:
      format = GST_AUDIO_FORMAT_UNKNOWN;
      break;
  }

  gst_audio_info_set_format (&dvdlpcmdec->info, format, rate, channels, NULL);
  if (channels < 9
      && channel_positions[channels - 1][0] !=
      GST_AUDIO_CHANNEL_POSITION_INVALID) {
    dvdlpcmdec->info.flags &= ~GST_AUDIO_FLAG_UNPOSITIONED;
    position = channel_positions[channels - 1];
    dvdlpcmdec->lpcm_layout = position;
    memcpy (dvdlpcmdec->info.position, position,
        sizeof (GstAudioChannelPosition) * channels);
    gst_audio_channel_positions_to_valid_order (dvdlpcmdec->info.position,
        channels);
  }

  dvdlpcmdec->width = width;

  res = gst_dvdlpcmdec_set_outcaps (dvdlpcmdec);

done:
  gst_object_unref (dvdlpcmdec);
  return res;


caps_parse_error:
  {
    GST_DEBUG_OBJECT (dvdlpcmdec, "Couldn't get parameters; missing caps?");
    gst_object_unref (dvdlpcmdec);
    return FALSE;
  }
}
