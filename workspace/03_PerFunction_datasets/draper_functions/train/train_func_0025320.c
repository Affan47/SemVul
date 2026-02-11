crypto_ctx_free(crypto_ctx *ctx)
{
	if (ctx) {
		int i;

		for (i = 0; i < ctx->num; i++)
			gnutls_x509_crt_deinit(ctx->stack[i]);
		gnutls_free(ctx->stack);
		memset(ctx, 0, sizeof(crypto_ctx));
		gnutls_free(ctx);
	}
}
