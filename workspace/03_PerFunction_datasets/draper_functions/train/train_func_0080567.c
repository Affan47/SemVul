encrypt_memcpy(unsigned char *dst, unsigned char *src, int len, unsigned char *iv, ast_aes_encrypt_key *ecx)
{
	unsigned char curblock[16];
	int x;
	memcpy(curblock, iv, sizeof(curblock));
	while(len > 0) {
		for (x=0;x<16;x++)
			curblock[x] ^= src[x];
		ast_aes_encrypt(curblock, dst, ecx);
		memcpy(curblock, dst, sizeof(curblock));
		dst += 16;
		src += 16;
		len -= 16;
	}
	return 0;
}
