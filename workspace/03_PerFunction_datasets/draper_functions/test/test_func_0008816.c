get_format(bgav_stream_t * s)
  {
  mad_priv_t * priv;
  const char * version_string;

  priv = s->data.audio.decoder->priv;


  s->data.audio.format.samplerate = priv->frame.header.samplerate;

  if(priv->frame.header.mode == MAD_MODE_SINGLE_CHANNEL)
    s->data.audio.format.num_channels = 1;
  else
    s->data.audio.format.num_channels = 2;

  s->data.audio.format.samplerate = priv->frame.header.samplerate;
  s->data.audio.format.sample_format = GAVL_SAMPLE_FLOAT;
  s->data.audio.format.interleave_mode = GAVL_INTERLEAVE_NONE;
  s->data.audio.format.samples_per_frame =
    MAD_NSBSAMPLES(&priv->frame.header) * 32;

  if(!s->codec_bitrate)
    {
    if(s->container_bitrate == BGAV_BITRATE_VBR)
      s->codec_bitrate = BGAV_BITRATE_VBR;
    else
      s->codec_bitrate = priv->frame.header.bitrate;
    }
  gavl_set_channel_setup(&s->data.audio.format);

  if(priv->frame.header.flags & MAD_FLAG_MPEG_2_5_EXT)
    {
    if(priv->frame.header.layer == 3)
      s->data.audio.preroll = s->data.audio.format.samples_per_frame * 30;
    else
      s->data.audio.preroll = s->data.audio.format.samples_per_frame;
    version_string = "2.5";
    }
  else if(priv->frame.header.flags & MAD_FLAG_LSF_EXT)
    {
    if(priv->frame.header.layer == 3)
      s->data.audio.preroll = s->data.audio.format.samples_per_frame * 30;
    else
      s->data.audio.preroll = s->data.audio.format.samples_per_frame;
    version_string = "2";
    }
  else
    {
    if(priv->frame.header.layer == 3)
      s->data.audio.preroll = s->data.audio.format.samples_per_frame * 10;
    else
      s->data.audio.preroll = s->data.audio.format.samples_per_frame;
    version_string = "1";
    }

  gavl_metadata_set_nocpy(&s->m, GAVL_META_FORMAT,
                          bgav_sprintf("MPEG-%s layer %d",
                                       version_string, priv->frame.header.layer));

  priv->audio_frame = gavl_audio_frame_create(&s->data.audio.format);
  }
