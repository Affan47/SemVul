bgav_subtitle_reader_has_subtitle(bgav_stream_t * s)
  {
  bgav_subtitle_reader_context_t * ctx;
  ctx = s->data.subtitle.subreader;

  if(!ctx->has_subtitle)
    {
    if(ctx->reader->read_subtitle_text && ctx->reader->read_subtitle_text(s))
      ctx->has_subtitle = 1;
    else if(ctx->reader->read_subtitle_overlay && ctx->reader->read_subtitle_overlay(s))
      ctx->has_subtitle = 1;
    }
  return ctx->has_subtitle;
  }
