ssl3_digest_cached_records(SSL *s)
	{
	int i;
	long mask;
	const EVP_MD *md;
	long hdatalen;
	void *hdata;


	ssl3_free_digest_list(s);
	s->s3->handshake_dgst = OPENSSL_malloc(SSL_MAX_DIGEST * sizeof(EVP_MD_CTX *));
	memset(s->s3->handshake_dgst,0,SSL_MAX_DIGEST *sizeof(EVP_MD_CTX *));
	hdatalen = BIO_get_mem_data(s->s3->handshake_buffer,&hdata);
	if (hdatalen <= 0)
		{
		SSLerr(SSL_F_SSL3_DIGEST_CACHED_RECORDS, SSL_R_BAD_HANDSHAKE_LENGTH);
		return 0;
		}


	for (i=0;ssl_get_handshake_digest(i,&mask,&md); i++)
		{
		if ((mask & ssl_get_algorithm2(s)) && md)
			{
			s->s3->handshake_dgst[i]=EVP_MD_CTX_create();
#ifdef OPENSSL_FIPS
			if (EVP_MD_nid(md) == NID_md5)
				{
				EVP_MD_CTX_set_flags(s->s3->handshake_dgst[i],
						EVP_MD_CTX_FLAG_NON_FIPS_ALLOW);
				}
#endif
			EVP_DigestInit_ex(s->s3->handshake_dgst[i],md,NULL);
			EVP_DigestUpdate(s->s3->handshake_dgst[i],hdata,hdatalen);
			}
		else
			{
			s->s3->handshake_dgst[i]=NULL;
			}
		}
	if (!(s->s3->flags & TLS1_FLAGS_KEEP_HANDSHAKE))
		{

		BIO_free(s->s3->handshake_buffer);
		s->s3->handshake_buffer = NULL;
		}

	return 1;
	}
