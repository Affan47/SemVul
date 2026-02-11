opensslgost_tofile(const dst_key_t *key, const char *directory) {
	EVP_PKEY *pkey;
	EC_KEY *eckey;
	const BIGNUM *privkey;
	dst_private_t priv;
	isc_result_t ret;
	unsigned char *buf = NULL;

	if (key->keydata.pkey == NULL)
		return (DST_R_NULLKEY);

	if (key->external) {
		priv.nelements = 0;
		return (dst__privstruct_writefile(key, &priv, directory));
	}

	pkey = key->keydata.pkey;
	eckey = EVP_PKEY_get0(pkey);
	if (eckey == NULL)
		return (dst__openssl_toresult(DST_R_OPENSSLFAILURE));
	privkey = EC_KEY_get0_private_key(eckey);
	if (privkey == NULL)
		return (ISC_R_FAILURE);

	buf = isc_mem_get(key->mctx, BN_num_bytes(privkey));
	if (buf == NULL)
		return (ISC_R_NOMEMORY);

	priv.elements[0].tag = TAG_GOST_PRIVRAW;
	priv.elements[0].length = BN_num_bytes(privkey);
	BN_bn2bin(privkey, buf);
	priv.elements[0].data = buf;
	priv.nelements = 1;

	ret = dst__privstruct_writefile(key, &priv, directory);

	if (buf != NULL)
		isc_mem_put(key->mctx, buf, BN_num_bytes(privkey));
	return (ret);
}
