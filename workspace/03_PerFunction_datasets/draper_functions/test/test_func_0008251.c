crypto_chacha20_setkey(struct crypto_tfm *tfm, const u8 *key,
			   unsigned int keysize)
{
	struct chacha20_ctx *ctx = crypto_tfm_ctx(tfm);
	int i;

	if (keysize != CHACHA20_KEY_SIZE)
		return -EINVAL;

	for (i = 0; i < ARRAY_SIZE(ctx->key); i++)
		ctx->key[i] = le32_to_cpuvp(key + i * sizeof(u32));

	return 0;
}
