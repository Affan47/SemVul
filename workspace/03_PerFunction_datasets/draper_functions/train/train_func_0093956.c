make_secret(uint8_t *digest, const uint8_t *vector,
			const char *secret, const uint8_t *value)
{
	FR_MD5_CTX context;
        int             i;

	fr_MD5Init(&context);
	fr_MD5Update(&context, vector, AUTH_VECTOR_LEN);
	fr_MD5Update(&context, (const uint8_t *) secret, strlen(secret));
	fr_MD5Final(digest, &context);

        for ( i = 0; i < AUTH_VECTOR_LEN; i++ ) {
		digest[i] ^= value[i];
        }
}
