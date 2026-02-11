ssl_free(BIO *a)
	{
	BIO_SSL *bs;

	if (a == NULL) return(0);
	bs=(BIO_SSL *)a->ptr;
	if (bs->ssl != NULL) SSL_shutdown(bs->ssl);
	if (a->shutdown)
		{
		if (a->init && (bs->ssl != NULL))
			SSL_free(bs->ssl);
		a->init=0;
		a->flags=0;
		}
	if (a->ptr != NULL)
		OPENSSL_free(a->ptr);
	return(1);
	}
