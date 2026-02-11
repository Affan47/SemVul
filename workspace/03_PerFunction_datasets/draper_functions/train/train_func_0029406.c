init_mad(bgav_stream_t * s)
  {
  mad_priv_t * priv;

  priv = calloc(1, sizeof(*priv));
  s->data.audio.decoder->priv = priv;

  mad_frame_init(&priv->frame);
  mad_synth_init(&priv->synth);
  mad_stream_init(&priv->stream);


  get_data(s);

  priv->do_init = 1;

  if(!decode_frame_mad(s))
    return 0;

  priv->do_init = 0;

  return 1;
  }
