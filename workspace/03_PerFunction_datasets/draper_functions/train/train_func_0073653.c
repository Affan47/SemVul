logflush(void *handle) {
    struct LogContext *ctx = (struct LogContext *)handle;
    if (ctx->cfg.logtype > 0)
	if (ctx->state == L_OPEN)
	    fflush(ctx->lgfp);
}
