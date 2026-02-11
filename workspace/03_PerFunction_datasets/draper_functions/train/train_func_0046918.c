get_remctx (ProfContext *ctx, intptr_t remctx_id)
{
	if (ctx->current_remctx && ctx->current_remctx->remctx_id == remctx_id)
		return ctx->current_remctx;

	RemCtxContext *remctx = ctx->remctxs;

	while (remctx) {
		if (remctx->remctx_id == remctx_id)
			return remctx;

		remctx = remctx->next;
	}

	remctx = (RemCtxContext *)calloc (sizeof (RemCtxContext), 1);
	remctx->next = ctx->remctxs;
	ctx->remctxs = remctx;
	remctx->remctx_id = remctx_id;

	return remctx;
}
