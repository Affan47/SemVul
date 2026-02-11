sign_key_md5_fingerprint(unsigned char* keyblob,
		unsigned int keybloblen) {

	char * ret;
	hash_state hs;
	unsigned char hash[MD5_HASH_SIZE];
	unsigned int i;
	unsigned int buflen;

	md5_init(&hs);


	md5_process(&hs, keyblob, keybloblen);

	md5_done(&hs, hash);


	buflen = 4 + 3*MD5_HASH_SIZE;
	ret = (char*)m_malloc(buflen);

	memset(ret, 'Z', buflen);
	strcpy(ret, "md5 ");

	for (i = 0; i < MD5_HASH_SIZE; i++) {
		unsigned int pos = 4 + i*3;
		ret[pos] = hexdig(hash[i] >> 4);
		ret[pos+1] = hexdig(hash[i] & 0x0f);
		ret[pos+2] = ':';
	}
	ret[buflen-1] = 0x0;

	return ret;
}
