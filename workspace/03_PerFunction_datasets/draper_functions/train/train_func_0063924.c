resync_flv(bgav_demuxer_context_t * ctx, bgav_stream_t * s)
  {
  flv_priv_t * priv;
  priv = ctx->priv;

  if(s->type == BGAV_STREAM_AUDIO)
    {
    priv->audio_sample_counter = s->in_position;
    }
  }
