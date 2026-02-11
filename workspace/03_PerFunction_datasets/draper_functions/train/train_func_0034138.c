resync_a52(bgav_stream_t * s)
  {
  a52_priv * priv;

  priv = s->data.audio.decoder->priv;
  if(!priv->state)
    return;

  a52_free(priv->state);
  priv->state = a52_init(0);
  priv->samples = a52_samples(priv->state);
  memset(priv->samples, 0, 256*6*sizeof(*priv->samples));

#if 0
  p = bgav_stream_peek_packet_read(s, 1);
  if(p->pts == s->start_time)
    first_packet = 1;
  else
    first_packet = 0;

  decode_frame_a52(s);


  if(!first_packet)
    {
    s->data.audio.frame->valid_samples = 0;
    p = bgav_stream_peek_packet_read(s, 1);
    s->out_time = p->pts;
    bgav_log(s->opt, BGAV_LOG_DEBUG, LOG_DOMAIN, "Resync %"PRId64, s->out_time);
    }
#endif
  }
