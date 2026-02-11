SHA384(const unsigned char *d, size_t n, unsigned char *md)
	{
	SHA512_CTX c;
	static unsigned char m[SHA384_DIGEST_LENGTH];

	if (md == NULL) md=m;
	SHA384_Init(&c);
	SHA512_Update(&c,d,n);
	SHA512_Final(md,&c);
	OPENSSL_cleanse(&c,sizeof(c));
	return(md);
	}
