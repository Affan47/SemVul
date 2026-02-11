kmod_set_log_fn(struct kmod_ctx *ctx,
					void (*log_fn)(void *data,
						int priority, const char *file,
						int line, const char *fn,
						const char *format, va_list args),
					const void *data)
{
	if (ctx == NULL)
		return;
	ctx->log_fn = log_fn;
	ctx->log_data = (void *)data;
	INFO(ctx, "custom logging function %p registered\n", log_fn);
}
