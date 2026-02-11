assuan_set_log_stream (assuan_context_t ctx, FILE *fp)
{
  if (ctx)
    {
      if (ctx->log_fp)
        fflush (ctx->log_fp);
      ctx->log_fp = fp;
      if (! _assuan_log)
	assuan_set_assuan_log_stream (fp);
    }
}
