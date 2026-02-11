pkey_dsa_verify(EVP_PKEY_CTX *ctx,
					const unsigned char *sig, size_t siglen,
					const unsigned char *tbs, size_t tbslen)
	{
	int ret, type;
	DSA_PKEY_CTX *dctx = ctx->data;
	DSA *dsa = ctx->pkey->pkey.dsa;

	if (dctx->md)
		type = EVP_MD_type(dctx->md);
	else
		type = NID_sha1;

	ret = DSA_verify(type, tbs, tbslen, sig, siglen, dsa);

	return ret;
	}
