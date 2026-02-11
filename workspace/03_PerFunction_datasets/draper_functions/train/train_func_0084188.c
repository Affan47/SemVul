evrpc_hook_associate_meta_(struct evrpc_hook_meta **pctx,
    struct evhttp_connection *evcon)
{
	struct evrpc_hook_meta *ctx = *pctx;
	if (ctx == NULL)
		*pctx = ctx = evrpc_hook_meta_new_();
	ctx->evcon = evcon;
}
