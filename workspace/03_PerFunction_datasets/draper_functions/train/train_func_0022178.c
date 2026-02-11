start_audio(bg_ogg_encoder_t * e, int stream)
  {
  int result;
  bg_ogg_audio_stream_t * s = &e->audio_streams[stream];

  if(s->ci)
    result =
      s->codec->init_audio_compressed(s->codec_priv, &s->format, s->ci, &e->metadata);
  else
    result = s->codec->init_audio(s->codec_priv, &s->format, &e->metadata);
  return 1;
  }
