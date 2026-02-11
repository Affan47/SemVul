alloc_hash(struct crypto_hash **tfm, char *tfm_name, int err_alg)
{
	if (!tfm_name[0])
		return NO_ERROR;

	*tfm = crypto_alloc_hash(tfm_name, 0, CRYPTO_ALG_ASYNC);
	if (IS_ERR(*tfm)) {
		*tfm = NULL;
		return err_alg;
	}

	return NO_ERROR;
}
