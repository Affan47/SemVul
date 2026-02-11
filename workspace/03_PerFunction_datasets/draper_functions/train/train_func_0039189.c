aa_restore_previous_label(u64 token)
{
	struct aa_task_ctx *ctx;
	struct cred *new = prepare_creds();
	if (!new)
		return -ENOMEM;

	ctx = cred_ctx(new);
	if (ctx->token != token) {
		abort_creds(new);
		return -EACCES;
	}

	if (!ctx->previous) {
		abort_creds(new);
		return 0;
	}

	aa_put_label(ctx->label);
	ctx->label = aa_get_newest_label(ctx->previous);
	BUG_ON(!ctx->label);

	aa_clear_task_ctx_trans(ctx);

	commit_creds(new);
	return 0;
}
