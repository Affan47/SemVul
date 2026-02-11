callback_for_level(struct webauth_context *ctx, enum webauth_log_level level)
{
    switch (level) {
    case WA_LOG_WARN:   return &ctx->warn;
    case WA_LOG_NOTICE: return &ctx->notice;
    case WA_LOG_INFO:   return &ctx->info;
    case WA_LOG_TRACE:  return &ctx->trace;
    default:            return NULL;
    }
}
