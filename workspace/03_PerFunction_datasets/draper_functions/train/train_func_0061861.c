qat_rsa_exit_tfm(struct crypto_akcipher *tfm)
{
	struct qat_rsa_ctx *ctx = akcipher_tfm_ctx(tfm);
	struct device *dev = &GET_DEV(ctx->inst->accel_dev);

	if (ctx->n)
		dma_free_coherent(dev, ctx->key_sz, ctx->n, ctx->dma_n);
	if (ctx->e)
		dma_free_coherent(dev, ctx->key_sz, ctx->e, ctx->dma_e);
	if (ctx->d) {
		memset(ctx->d, '\0', ctx->key_sz);
		dma_free_coherent(dev, ctx->key_sz, ctx->d, ctx->dma_d);
	}
	qat_crypto_put_instance(ctx->inst);
	ctx->n = NULL;
	ctx->d = NULL;
	ctx->d = NULL;
}
