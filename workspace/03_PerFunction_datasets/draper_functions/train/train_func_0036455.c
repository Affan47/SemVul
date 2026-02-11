pkey_cmac_ctrl_str(EVP_PKEY_CTX *ctx,
			const char *type, const char *value)
	{
	if (!value)
		{
		return 0;
		}
	if (!strcmp(type, "key"))
		{
		void *p = (void *)value;
		return pkey_cmac_ctrl(ctx, EVP_PKEY_CTRL_SET_MAC_KEY,
								strlen(p), p);
		}
	if (!strcmp(type, "cipher"))
		{
		const EVP_CIPHER *c;
		c = EVP_get_cipherbyname(value);
		if (!c)
			return 0;
		return pkey_cmac_ctrl(ctx, EVP_PKEY_CTRL_CIPHER, -1, (void *)c);
		}
	if (!strcmp(type, "hexkey"))
		{
		unsigned char *key;
		int r;
		long keylen;
		key = string_to_hex(value, &keylen);
		if (!key)
			return 0;
		r = pkey_cmac_ctrl(ctx, EVP_PKEY_CTRL_SET_MAC_KEY, keylen, key);
		OPENSSL_free(key);
		return r;
		}
	return -2;
	}
