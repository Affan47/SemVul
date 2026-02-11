dst_hmac_md5_verify(const int mode, DST_KEY *d_key, void **context,
		const u_char *data, const int len,
		const u_char *signature, const int sig_len)
{
	HMAC_Key *key;
	MD5_CTX *ctx = NULL;

	if (d_key == NULL || d_key->dk_KEY_struct == NULL)
		return (-1);

	if (mode & SIG_MODE_INIT)
		ctx = (MD5_CTX *) malloc(sizeof(*ctx));
	else if (context)
		ctx = (MD5_CTX *) *context;
	if (ctx == NULL)
		return (-1);

	key = (HMAC_Key *) d_key->dk_KEY_struct;
	if (mode & SIG_MODE_INIT) {
		MD5Init(ctx);
		MD5Update(ctx, key->hk_ipad, HMAC_LEN);
	}
	if ((mode & SIG_MODE_UPDATE) && (data && len > 0))
		MD5Update(ctx, data, len);

	if (mode & SIG_MODE_FINAL) {
		u_char digest[MD5_LEN];
		if (signature == NULL || key == NULL || sig_len != MD5_LEN)
			return (VERIFY_FINAL_FAILURE);
		MD5Final(digest, ctx);


		MD5Init(ctx);
		MD5Update(ctx, key->hk_opad, HMAC_LEN);
		MD5Update(ctx, digest, MD5_LEN);
		MD5Final(digest, ctx);

		SAFE_FREE(ctx);
		if (memcmp(digest, signature, MD5_LEN) != 0)
			return (VERIFY_FINAL_FAILURE);
	}
	else {
		if (context == NULL)
			return (-1);
		*context = (void *) ctx;
	}
	return (0);
}
