jgdi_rmon_mprintf(rmon_ctx_t* ctx, int debug_class, const char* fmt, va_list args)
{
   jgdi_rmon_ctx_t *myctx = (jgdi_rmon_ctx_t*)ctx->ctx;
   log_level_t level = get_rmon_log_level(TOP_LAYER, debug_class);

   if (jgdi_is_loggable(myctx->env, myctx->logger, level)) {
      dstring ds = DSTRING_INIT;

      sge_dstring_vsprintf(&ds, fmt, args);

      jgdi_log(myctx->env, myctx->logger, level, sge_dstring_get_string(&ds));
      sge_dstring_free(&ds);
   }
}
