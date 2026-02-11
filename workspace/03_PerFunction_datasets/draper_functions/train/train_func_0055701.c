next_packet_mxf(bgav_demuxer_context_t * ctx)
  {
  bgav_stream_t * s;
  stream_priv_t * sp;

  s = ctx->request_stream;
  if(s)
    sp = s->priv;
  else
    sp = NULL;

  while(!s || !sp->next_packet(ctx, s))
    {
    if(sp) sp->eof = 1;
    s = next_stream(ctx->tt->cur->audio_streams,ctx->tt->cur->num_audio_streams);
    if(!s)
      s = next_stream(ctx->tt->cur->video_streams,ctx->tt->cur->num_video_streams);
    if(!s)
      s = next_stream(ctx->tt->cur->subtitle_streams,ctx->tt->cur->num_subtitle_streams);
    if(!s)
      return 0;
    sp = s->priv;
    }
  return 1;
  }
