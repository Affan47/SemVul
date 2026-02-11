crypt_aescbc_encrypt(unsigned char *key, unsigned int keybits, unsigned char *ivec, unsigned int iveclen, unsigned char *inbuf, unsigned int inlen, unsigned char *outbuf, unsigned int *outlen) {
	unsigned char ivecbuf[AES_BLOCK_SIZE];
	unsigned char *databuf = (unsigned char *)cryptbuf;
	int databuflen;
	AES_KEY akey;

	if(keybits != 128 && keybits != 192 && keybits != 256) return CRYPT_MISCERR;

	crypt_aescbc_getivec(ivec, iveclen, ivecbuf);

	databuflen = crypt_aescbc_getencryptbuflen(inlen);
	if(CRYPTBUFLEN < databuflen) return CRYPT_TOOBIG;
	memcpy(databuf, inbuf, inlen);

	RAND_pseudo_bytes(databuf + inlen, databuflen - inlen - 1);

	databuf[databuflen - 1] = databuflen - inlen - 1;

	AES_set_encrypt_key(key, keybits, &akey);

	AES_cbc_encrypt(databuf, outbuf, databuflen, &akey, ivecbuf, AES_ENCRYPT);

	*outlen = databuflen;
	return CRYPT_OK;
}
