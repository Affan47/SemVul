evt_ctx_init(const char *prog, int syslog_fac)
{
  EVTCONTEXT *ctx;

  ctx = (EVTCONTEXT *) calloc(sizeof(*ctx), 1);
  if (ctx)
    {
      strcpy(ctx->ec_formatter, "plain");
      strcpy(ctx->ec_outmethod, "local");
      ctx->ec_ref = 1;
      ctx->ec_flags = EF_INITIALIZED;
      ctx->ec_prog = (char *) prog;
      ctx->ec_syslog_fac = syslog_fac;
      evt_ctx_tag_hook_add(ctx, evtrec_add_standard_tags, NULL);
#ifndef _MSC_VER
      evt_syslog_wrapper_init();
#endif
      evt_read_config(ctx);
    }

  return ctx;
}
