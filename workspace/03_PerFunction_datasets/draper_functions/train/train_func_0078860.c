free_sign_context(sign_context_t *ctx)
{
	if (ctx == NULL) {
		DBG_NULL;
		return;
	}

	if (ctx->tsig_key.name) {
		knot_tsig_key_free(&ctx->tsig_key);
	}

	if (ctx->dnssec_key.name) {
		knot_dnssec_key_free(&ctx->dnssec_key);
	}

	free(ctx->digest);

	memset(ctx, '\0', sizeof(sign_context_t));
}
