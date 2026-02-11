next_packet_adif(bgav_demuxer_context_t * ctx)
  {
  bgav_stream_t * s;
  bgav_packet_t * p;
  aac_priv_t * priv;
  int bytes_read;
  priv = ctx->priv;
  s = ctx->tt->cur->audio_streams;


  p = bgav_stream_get_packet_write(s);
  bgav_packet_alloc(p, BYTES_TO_READ);

  bytes_read = bgav_input_read_data(ctx->input, p->data, BYTES_TO_READ);
  if(!bytes_read)
    return 0;
  p->data_size = bytes_read;

  bgav_stream_done_packet_write(s, p);
  return 1;
  }
