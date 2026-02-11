EVP_PKEY_CTX_free(EVP_PKEY_CTX *ctx)
	{
	if (ctx == NULL)
		return;
	if (ctx->pmeth && ctx->pmeth->cleanup)
		ctx->pmeth->cleanup(ctx);
	if (ctx->pkey)
		EVP_PKEY_free(ctx->pkey);
	if (ctx->peerkey)
		EVP_PKEY_free(ctx->peerkey);
#ifndef OPENSSL_NO_ENGINE
	if(ctx->engine)


		ENGINE_finish(ctx->engine);
#endif
	OPENSSL_free(ctx);
	}
