ddjvu_cache_get_size(ddjvu_context_t *ctx)
{
  G_TRY
    {
      GMonitorLock lock(&ctx->monitor);
      if (ctx->cache)
        return ctx->cache->get_max_size();
    }
  G_CATCH(ex)
    {
      ERROR1(ctx, ex);
    }
  G_ENDCATCH;
  return 0;
}
