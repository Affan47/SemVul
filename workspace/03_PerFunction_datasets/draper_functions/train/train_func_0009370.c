ssl3_generate_master_secret(SSL *s, unsigned char *out, unsigned char *p,
	     int len)
	{
	static const unsigned char *salt[3]={
#ifndef CHARSET_EBCDIC
		(const unsigned char *)"A",
		(const unsigned char *)"BB",
		(const unsigned char *)"CCC",
#else
		(const unsigned char *)"\x41",
		(const unsigned char *)"\x42\x42",
		(const unsigned char *)"\x43\x43\x43",
#endif
		};
	unsigned char buf[EVP_MAX_MD_SIZE];
	EVP_MD_CTX ctx;
	int i,ret=0;
	unsigned int n;

	EVP_MD_CTX_init(&ctx);
	for (i=0; i<3; i++)
		{
		EVP_DigestInit_ex(&ctx,s->ctx->sha1, NULL);
		EVP_DigestUpdate(&ctx,salt[i],strlen((const char *)salt[i]));
		EVP_DigestUpdate(&ctx,p,len);
		EVP_DigestUpdate(&ctx,&(s->s3->client_random[0]),
			SSL3_RANDOM_SIZE);
		EVP_DigestUpdate(&ctx,&(s->s3->server_random[0]),
			SSL3_RANDOM_SIZE);
		EVP_DigestFinal_ex(&ctx,buf,&n);

		EVP_DigestInit_ex(&ctx,s->ctx->md5, NULL);
		EVP_DigestUpdate(&ctx,p,len);
		EVP_DigestUpdate(&ctx,buf,n);
		EVP_DigestFinal_ex(&ctx,out,&n);
		out+=n;
		ret+=n;
		}
	EVP_MD_CTX_cleanup(&ctx);
	return(ret);
	}
