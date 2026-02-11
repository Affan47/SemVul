assuan_set_log_stream (assuan_context_t ctx, FILE *fp)
{
  if (ctx)
    {
      if (ctx->log_fp)
        fflush (ctx->log_fp);
      ctx->log_fp = fp;
      _assuan_set_default_log_stream (fp);
    }
}
