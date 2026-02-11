parse_header (GstDvdLpcmDec * dec, guint32 header)
{
  GstAudioFormat format;
  gint rate, channels, width;


  dec->dynamic_range = header & 0xff;

  dec->mute = (header & 0x400000) != 0;
  dec->emphasis = (header & 0x800000) != 0;


  switch (header & 0xC000) {
    case 0x8000:

      format = GST_AUDIO_FORMAT_S24BE;
      width = 24;
      break;
    case 0x4000:

      format = GST_AUDIO_FORMAT_S24BE;
      width = 20;
      break;
    default:
      format = GST_AUDIO_FORMAT_S16BE;
      width = 16;
      break;
  }

  dec->width = width;


  switch (header & 0x3000) {
    case 0x0000:
      rate = 48000;
      break;
    case 0x1000:
      rate = 96000;
      break;
    case 0x2000:
      rate = 44100;
      break;
    case 0x3000:
      rate = 32000;
      break;
    default:
      rate = 0;
      break;
  }


  channels = ((header >> 8) & 0x7) + 1;

  gst_audio_info_set_format (&dec->info, format, rate, channels, NULL);
  if (channels < 9
      && channel_positions[channels - 1][0] !=
      GST_AUDIO_CHANNEL_POSITION_INVALID) {
    const GstAudioChannelPosition *position;

    dec->info.flags &= ~GST_AUDIO_FLAG_UNPOSITIONED;
    position = channel_positions[channels - 1];
    dec->lpcm_layout = position;
    memcpy (dec->info.position, position,
        sizeof (GstAudioChannelPosition) * channels);
    gst_audio_channel_positions_to_valid_order (dec->info.position, channels);
  }
}
