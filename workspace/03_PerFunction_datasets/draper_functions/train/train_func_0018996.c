crypto_skcipher_init_tfm(struct crypto_tfm *tfm)
{
	if (tfm->__crt_alg->cra_type == &crypto_blkcipher_type)
		return crypto_init_skcipher_ops_blkcipher(tfm);

	BUG_ON(tfm->__crt_alg->cra_type != &crypto_ablkcipher_type &&
	       tfm->__crt_alg->cra_type != &crypto_givcipher_type);

	return crypto_init_skcipher_ops_ablkcipher(tfm);
}
