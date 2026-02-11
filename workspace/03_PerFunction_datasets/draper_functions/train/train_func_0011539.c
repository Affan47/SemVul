aead_init_geniv(struct crypto_aead *aead)
{
	struct aead_geniv_ctx *ctx = crypto_aead_ctx(aead);
	struct aead_instance *inst = aead_alg_instance(aead);
	struct crypto_aead *child;
	int err;

	spin_lock_init(&ctx->lock);

	err = crypto_get_default_rng();
	if (err)
		goto out;

	err = crypto_rng_get_bytes(crypto_default_rng, ctx->salt,
				   crypto_aead_ivsize(aead));
	crypto_put_default_rng();
	if (err)
		goto out;

	ctx->null = crypto_get_default_null_skcipher();
	err = PTR_ERR(ctx->null);
	if (IS_ERR(ctx->null))
		goto out;

	child = crypto_spawn_aead(aead_instance_ctx(inst));
	err = PTR_ERR(child);
	if (IS_ERR(child))
		goto drop_null;

	ctx->child = child;
	crypto_aead_set_reqsize(aead, crypto_aead_reqsize(child) +
				      sizeof(struct aead_request));

	err = 0;

out:
	return err;

drop_null:
	crypto_put_default_null_skcipher();
	goto out;
}
