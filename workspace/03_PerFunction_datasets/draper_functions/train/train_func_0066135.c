aead_prepare_alg(struct aead_alg *alg)
{
	struct crypto_alg *base = &alg->base;

	if (max(alg->maxauthsize, alg->ivsize) > PAGE_SIZE / 8)
		return -EINVAL;

	base->cra_type = &crypto_aead_type;
	base->cra_flags &= ~CRYPTO_ALG_TYPE_MASK;
	base->cra_flags |= CRYPTO_ALG_TYPE_AEAD;

	return 0;
}
