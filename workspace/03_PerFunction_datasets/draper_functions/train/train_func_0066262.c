assuan_get_flag (assuan_context_t ctx, assuan_flag_t flag)
{
  int res = 0;
  TRACE_BEG1 (ctx, ASSUAN_LOG_CTX, "assuan_get_flag", ctx,
	      "flag=%i", flag);

  if (! ctx)
    return 0;

  switch (flag)
    {
    case ASSUAN_NO_WAITPID:
      res = ctx->flags.no_waitpid;
      break;

    case ASSUAN_CONFIDENTIAL:
      res = ctx->flags.confidential;
      break;

    case ASSUAN_NO_FIXSIGNALS:
      res = ctx->flags.no_fixsignals;
      break;
    }

  return TRACE_SUC1 ("flag_value=%i", res);
}
