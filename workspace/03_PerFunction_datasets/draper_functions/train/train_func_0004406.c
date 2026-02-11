pbkdf2_hmac_sha256(const uint8_t *pass, int passlen, uint8_t *salt, int saltlen, uint32_t iterations, uint8_t *key, int keylen, void (*progress_callback)(uint32_t current, uint32_t total))
{
	const uint32_t HMACLEN = 256/8;
	uint32_t i, j, k;
	uint8_t f[HMACLEN], g[HMACLEN];
	uint32_t blocks = keylen / HMACLEN;
	if (keylen & (HMACLEN - 1)) {
		blocks++;
	}
	for (i = 1; i <= blocks; i++) {
		salt[saltlen    ] = (i >> 24) & 0xFF;
		salt[saltlen + 1] = (i >> 16) & 0xFF;
		salt[saltlen + 2] = (i >> 8) & 0xFF;
		salt[saltlen + 3] = i & 0xFF;
		hmac_sha256(pass, passlen, salt, saltlen + 4, g);
		memcpy(f, g, HMACLEN);
		for (j = 1; j < iterations; j++) {
			hmac_sha256(pass, passlen, g, HMACLEN, g);
			for (k = 0; k < HMACLEN; k++) {
				f[k] ^= g[k];
			}
			if (progress_callback && (j % 256 == 255)) {
				progress_callback(j + 1, iterations);
			}
		}
		if (i == blocks && (keylen & (HMACLEN - 1))) {
			memcpy(key + HMACLEN * (i - 1), f, keylen & (HMACLEN - 1));
		} else {
			memcpy(key + HMACLEN * (i - 1), f, HMACLEN);
		}
	}
	MEMSET_BZERO(f, sizeof(f));
	MEMSET_BZERO(g, sizeof(g));
}
