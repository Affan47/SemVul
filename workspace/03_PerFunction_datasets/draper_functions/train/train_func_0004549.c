F(GChecksum *checksum, const char *password, size_t password_len,
				const char *salt, size_t salt_len,
				unsigned int iterations, unsigned int count,
							unsigned char *digest)
{
	unsigned char tmp1[SHA1_MAC_LEN];
	unsigned char tmp2[SHA1_MAC_LEN];
	unsigned char buf[36];
	unsigned int i, j;

	memcpy(buf, salt, salt_len);
	buf[salt_len + 0] = (count >> 24) & 0xff;
	buf[salt_len + 1] = (count >> 16) & 0xff;
	buf[salt_len + 2] = (count >> 8) & 0xff;
	buf[salt_len + 3] = count & 0xff;

	__hmac_sha1(checksum, password, password_len,
					buf, salt_len + 4, tmp1);
	memcpy(digest, tmp1, SHA1_MAC_LEN);

	for (i = 1; i < iterations; i++) {
		__hmac_sha1(checksum, password, password_len,
						tmp1, SHA1_MAC_LEN, tmp2);
		memcpy(tmp1, tmp2, SHA1_MAC_LEN);

		for (j = 0; j < SHA1_MAC_LEN; j++)
			digest[j] ^= tmp2[j];
	}
}
