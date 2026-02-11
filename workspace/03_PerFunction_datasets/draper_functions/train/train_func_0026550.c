call_proc(struct fuse_opt_context *ctx, const char *arg, int key,
		     int iso)
{
	if (key == FUSE_OPT_KEY_DISCARD)
		return 0;

	if (key != FUSE_OPT_KEY_KEEP && ctx->proc) {
		int res = ctx->proc(ctx->data, arg, key, &ctx->outargs);
		if (res == -1 || !res)
			return res;
	}
	if (iso)
		return add_opt(ctx, arg);
	else
		return add_arg(ctx, arg);
}
