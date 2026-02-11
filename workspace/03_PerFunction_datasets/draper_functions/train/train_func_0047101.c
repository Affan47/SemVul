hmacmd5_fromdns(dst_key_t *key, isc_buffer_t *data) {
	dst_hmacmd5_key_t *hkey;
	int keylen;
	isc_region_t r;
	isc_md5_t md5ctx;

	isc_buffer_remainingregion(data, &r);
	if (r.length == 0)
		return (ISC_R_SUCCESS);

	hkey = isc_mem_get(key->mctx, sizeof(dst_hmacmd5_key_t));
	if (hkey == NULL)
		return (ISC_R_NOMEMORY);

	memset(hkey->key, 0, sizeof(hkey->key));

	if (r.length > ISC_MD5_BLOCK_LENGTH) {
		isc_md5_init(&md5ctx);
		isc_md5_update(&md5ctx, r.base, r.length);
		isc_md5_final(&md5ctx, hkey->key);
		keylen = ISC_MD5_DIGESTLENGTH;
	} else {
		memmove(hkey->key, r.base, r.length);
		keylen = r.length;
	}

	key->key_size = keylen * 8;
	key->keydata.hmacmd5 = hkey;

	isc_buffer_forward(data, r.length);

	return (ISC_R_SUCCESS);
}
