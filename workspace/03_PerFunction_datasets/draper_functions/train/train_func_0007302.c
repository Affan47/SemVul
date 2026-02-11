qce_ablkcipher_init(struct crypto_tfm *tfm)
{
	struct qce_cipher_ctx *ctx = crypto_tfm_ctx(tfm);

	memset(ctx, 0, sizeof(*ctx));
	tfm->crt_ablkcipher.reqsize = sizeof(struct qce_cipher_reqctx);

	ctx->fallback = crypto_alloc_ablkcipher(crypto_tfm_alg_name(tfm),
						CRYPTO_ALG_TYPE_ABLKCIPHER,
						CRYPTO_ALG_ASYNC |
						CRYPTO_ALG_NEED_FALLBACK);
	if (IS_ERR(ctx->fallback))
		return PTR_ERR(ctx->fallback);

	return 0;
}
