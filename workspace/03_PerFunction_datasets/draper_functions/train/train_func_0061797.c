SSL_load_client_CA_file(const char *file)
	{
	BIO *in;
	X509 *x=NULL;
	X509_NAME *xn=NULL;
	STACK_OF(X509_NAME) *ret = NULL,*sk;

	sk=sk_X509_NAME_new(xname_cmp);

	in=BIO_new(BIO_s_file_internal());

	if ((sk == NULL) || (in == NULL))
		{
		SSLerr(SSL_F_SSL_LOAD_CLIENT_CA_FILE,ERR_R_MALLOC_FAILURE);
		goto err;
		}

	if (!BIO_read_filename(in,file))
		goto err;

	for (;;)
		{
		if (PEM_read_bio_X509(in,&x,NULL,NULL) == NULL)
			break;
		if (ret == NULL)
			{
			ret = sk_X509_NAME_new_null();
			if (ret == NULL)
				{
				SSLerr(SSL_F_SSL_LOAD_CLIENT_CA_FILE,ERR_R_MALLOC_FAILURE);
				goto err;
				}
			}
		if ((xn=X509_get_subject_name(x)) == NULL) goto err;

		xn=X509_NAME_dup(xn);
		if (xn == NULL) goto err;
		if (sk_X509_NAME_find(sk,xn) >= 0)
			X509_NAME_free(xn);
		else
			{
			sk_X509_NAME_push(sk,xn);
			sk_X509_NAME_push(ret,xn);
			}
		}

	if (0)
		{
err:
		if (ret != NULL) sk_X509_NAME_pop_free(ret,X509_NAME_free);
		ret=NULL;
		}
	if (sk != NULL) sk_X509_NAME_free(sk);
	if (in != NULL) BIO_free(in);
	if (x != NULL) X509_free(x);
	if (ret != NULL)
		ERR_clear_error();
	return(ret);
	}
