crypto_gcm_init_tfm(struct crypto_aead *tfm)
{
	struct aead_instance *inst = aead_alg_instance(tfm);
	struct gcm_instance_ctx *ictx = aead_instance_ctx(inst);
	struct crypto_gcm_ctx *ctx = crypto_aead_ctx(tfm);
	struct crypto_ablkcipher *ctr;
	struct crypto_ahash *ghash;
	unsigned long align;
	int err;

	ghash = crypto_spawn_ahash(&ictx->ghash);
	if (IS_ERR(ghash))
		return PTR_ERR(ghash);

	ctr = crypto_spawn_skcipher(&ictx->ctr);
	err = PTR_ERR(ctr);
	if (IS_ERR(ctr))
		goto err_free_hash;

	ctx->ctr = ctr;
	ctx->ghash = ghash;

	align = crypto_aead_alignmask(tfm);
	align &= ~(crypto_tfm_ctx_alignment() - 1);
	crypto_aead_set_reqsize(tfm,
		align + offsetof(struct crypto_gcm_req_priv_ctx, u) +
		max(sizeof(struct ablkcipher_request) +
		    crypto_ablkcipher_reqsize(ctr),
		    sizeof(struct ahash_request) +
		    crypto_ahash_reqsize(ghash)));

	return 0;

err_free_hash:
	crypto_free_ahash(ghash);
	return err;
}
