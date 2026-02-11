bgav_demuxer_stop(bgav_demuxer_context_t * ctx)
  {
  ctx->demuxer->close(ctx);
  ctx->priv = NULL;


  ctx->flags &= ~(BGAV_DEMUXER_SI_SEEKING |
                  BGAV_DEMUXER_HAS_TIMESTAMP_OFFSET);

  ctx->timestamp_offset = 0;
  if(ctx->si)
    {
    bgav_superindex_destroy(ctx->si);
    ctx->si = NULL;
    }

  }
