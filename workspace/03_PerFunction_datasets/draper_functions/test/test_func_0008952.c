seek_mpegts(bgav_demuxer_context_t * ctx, int64_t time, int scale)
  {
  int64_t total_packets;
  int64_t packet;
  int64_t position;

  mpegts_t * priv;
  priv = ctx->priv;

  reset_streams_priv(ctx->tt->cur);

  total_packets =
    (ctx->input->total_bytes - priv->first_packet_pos) / priv->packet_size;

  packet =
    (int64_t)((double)total_packets *
              (double)gavl_time_unscale(scale, time) /
              (double)(ctx->tt->cur->duration)+0.5);

  position = priv->first_packet_pos + packet * priv->packet_size;

  if(position < priv->first_packet_pos)
    position = priv->first_packet_pos;
  if(position >= ctx->input->total_bytes)
    position = ctx->input->total_bytes-1;

  bgav_input_seek(ctx->input, position, SEEK_SET);

  priv->do_sync = 1;
  while(!bgav_track_has_sync(ctx->tt->cur))
    {
    if(!next_packet_mpegts(ctx))
      break;
    }
  priv->do_sync = 0;
  }
