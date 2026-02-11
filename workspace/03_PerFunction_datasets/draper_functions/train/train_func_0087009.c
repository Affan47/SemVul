cleanup_stream_asf(bgav_stream_t * s)
  {
  asf_audio_stream_t * as;
  if(s->type == BGAV_STREAM_AUDIO)
    {
    as = s->priv;

    if(as->scramble_buffer)
      free(as->scramble_buffer);
    if(s->priv)
      free(s->priv);
    }
  else
    {
    if(s->priv)
      free(s->priv);
    }
  }
