client_cert_cb(ssl_handle ssl, X509 **x509, EVP_PKEY **pkey)
{
	struct tls_info *info=(struct tls_info *)SSL_get_app_data(ssl);
	int i;
	const char *pem_cert;
	size_t pem_cert_size;
	STACK_OF(X509_NAME) *client_cas;
	int cert_num=0;
	int rc;

	if (info->getpemclientcert4ca == NULL)
		return 0;

	rc=0;
	client_cas=SSL_get_client_CA_list(ssl);

	if (info->loadpemclientcert4ca)
		(*info->loadpemclientcert4ca)(info->app_data);

	for (cert_num=0; (*info->getpemclientcert4ca)(cert_num, &pem_cert,
						      &pem_cert_size,
						      info->app_data);
	     ++cert_num)
	{
		BIO *certbio;
		int err;
		X509 *x;

		ERR_clear_error();

		certbio=BIO_new_mem_buf((void *)pem_cert, pem_cert_size);

		if (!certbio)
		{
			rc= -1;
			break;
		}

		x=PEM_read_bio_X509(certbio, x509, NULL, NULL);

		if (!x)
		{
			BIO_free(certbio);
			continue;
		}

		for (i=0; client_cas && i<client_cas->stack.num; i++)
		{
			X509_NAME *cert=(X509_NAME *)client_cas->stack.data[i];

			if (X509_NAME_cmp(cert,
					  x->cert_info->issuer) == 0)
				break;
		}

		if (!client_cas || i >= client_cas->stack.num)
		{
			BIO_free(certbio);
			continue;
		}

		while ((x=PEM_read_bio_X509(certbio, NULL,
					    NULL, 0)) != NULL)
		{
			if (SSL_CTX_add_extra_chain_cert(SSL_get_SSL_CTX(ssl),
							 x)
			    != 1)
			{
				X509_free(x);
				rc= -1;
				break;
			}
		}

		err = ERR_peek_last_error();
		if (rc || ERR_GET_LIB(err) != ERR_LIB_PEM ||
		    ERR_GET_REASON(err) != PEM_R_NO_START_LINE)
		{
			BIO_free(certbio);
			continue;
		}
		BIO_free(certbio);

		ERR_clear_error();

		certbio=BIO_new_mem_buf((void *)pem_cert, pem_cert_size);

		if (!certbio)
		{
			rc= -1;
			break;
		}

		if (!PEM_read_bio_PrivateKey(certbio, pkey, NULL, NULL))
		{
			BIO_free(certbio);
			continue;
		}

		BIO_free(certbio);
		rc=1;
		break;
	}
	ERR_clear_error();
	(*info->releasepemclientcert4ca)(info->app_data);
	return rc;
}
