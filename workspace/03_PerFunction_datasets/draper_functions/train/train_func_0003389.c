next_packet_au(bgav_demuxer_context_t * ctx)
  {
  bgav_packet_t * p;
  bgav_stream_t * s;
  int bytes_read;
  au_priv_t * priv;
  s = &ctx->tt->cur->audio_streams[0];
  p = bgav_stream_get_packet_write(s);

  priv = ctx->priv;

  bgav_packet_alloc(p, s->data.audio.block_align * BLOCKS_PER_PACKET);

  p->pts = pos_2_time(ctx, ctx->input->position);
  PACKET_SET_KEYFRAME(p);
  bytes_read = bgav_input_read_data(ctx->input, p->data,
                                    s->data.audio.block_align * BLOCKS_PER_PACKET);
  p->data_size = bytes_read;
  bgav_stream_done_packet_write(s, p);
  if(!bytes_read)
    return 0;
  return 1;
  }
