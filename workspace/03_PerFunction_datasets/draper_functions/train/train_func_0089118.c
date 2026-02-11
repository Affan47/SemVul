hmac_md5(unsigned char *buffer, int buffer_len, unsigned char *key, int key_len,
	 unsigned char *digest)
{
	MD5_CTX context;
	unsigned char k_ipad[65];
	unsigned char k_opad[65];
	unsigned char tk[16];
	int i;


	memset(k_ipad, 0, sizeof (k_ipad));
	memset(k_opad, 0, sizeof (k_opad));
	memset(tk, 0, sizeof (tk));


	if (key_len > 64) {
		MD5_CTX tctx;


		MD5_Init(&tctx);
		MD5_Update(&tctx, key, key_len);
		MD5_Final(tk, &tctx);

		key = tk;
		key_len = 16;
	}


	memset(k_ipad, 0, sizeof (k_ipad));
	memset(k_opad, 0, sizeof (k_opad));
	memcpy(k_ipad, key, key_len);
	memcpy(k_opad, key, key_len);


	for (i = 0; i < 64; i++) {
		k_ipad[i] ^= 0x36;
		k_opad[i] ^= 0x5c;
	}


	MD5_Init(&context);
	MD5_Update(&context, k_ipad, 64);
	MD5_Update(&context, buffer, buffer_len);
	MD5_Final(digest, &context);


	MD5_Init(&context);
	MD5_Update(&context, k_opad, 64);
	MD5_Update(&context, digest, 16);
	MD5_Final(digest, &context);
}
