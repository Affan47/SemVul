X509_LOOKUP_free(X509_LOOKUP *ctx)
	{
	if (ctx == NULL) return;
	if (	(ctx->method != NULL) &&
		(ctx->method->free != NULL))
		(*ctx->method->free)(ctx);
	OPENSSL_free(ctx);
	}
