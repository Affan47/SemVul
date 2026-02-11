opensslrsa_fromdns(dst_key_t *key, isc_buffer_t *data) {
	RSA *rsa;
	isc_region_t r;
	unsigned int e_bytes;
#if USE_EVP
	EVP_PKEY *pkey;
#endif

	isc_buffer_remainingregion(data, &r);
	if (r.length == 0)
		return (ISC_R_SUCCESS);

	rsa = RSA_new();
	if (rsa == NULL)
		return (dst__openssl_toresult(ISC_R_NOMEMORY));
	SET_FLAGS(rsa);

	if (r.length < 1) {
		RSA_free(rsa);
		return (DST_R_INVALIDPUBLICKEY);
	}
	e_bytes = *r.base++;
	r.length--;

	if (e_bytes == 0) {
		if (r.length < 2) {
			RSA_free(rsa);
			return (DST_R_INVALIDPUBLICKEY);
		}
		e_bytes = ((*r.base++) << 8);
		e_bytes += *r.base++;
		r.length -= 2;
	}

	if (r.length < e_bytes) {
		RSA_free(rsa);
		return (DST_R_INVALIDPUBLICKEY);
	}
	rsa->e = BN_bin2bn(r.base, e_bytes, NULL);
	r.base += e_bytes;
	r.length -= e_bytes;

	rsa->n = BN_bin2bn(r.base, r.length, NULL);

	key->key_size = BN_num_bits(rsa->n);

	isc_buffer_forward(data, r.length);

#if USE_EVP
	pkey = EVP_PKEY_new();
	if (pkey == NULL) {
		RSA_free(rsa);
		return (ISC_R_NOMEMORY);
	}
	if (!EVP_PKEY_set1_RSA(pkey, rsa)) {
		EVP_PKEY_free(pkey);
		RSA_free(rsa);
		return (dst__openssl_toresult(DST_R_OPENSSLFAILURE));
	}
	key->keydata.pkey = pkey;
	RSA_free(rsa);
#else
	key->keydata.rsa = rsa;
#endif

	return (ISC_R_SUCCESS);
}
