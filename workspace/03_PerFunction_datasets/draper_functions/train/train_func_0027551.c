X509_ocspid_print (BIO *bp, X509 *x)
	{
	unsigned char *der=NULL ;
	unsigned char *dertmp;
	int derlen;
	int i;
	unsigned char SHA1md[SHA_DIGEST_LENGTH];


	if (BIO_printf(bp,"        Subject OCSP hash: ") <= 0)
		goto err;
	derlen = i2d_X509_NAME(x->cert_info->subject, NULL);
	if ((der = dertmp = (unsigned char *)OPENSSL_malloc (derlen)) == NULL)
		goto err;
	i2d_X509_NAME(x->cert_info->subject, &dertmp);

	if (!EVP_Digest(der, derlen, SHA1md, NULL, EVP_sha1(), NULL))
		goto err;
	for (i=0; i < SHA_DIGEST_LENGTH; i++)
		{
		if (BIO_printf(bp,"%02X",SHA1md[i]) <= 0) goto err;
		}
	OPENSSL_free (der);
	der=NULL;


	if (BIO_printf(bp,"\n        Public key OCSP hash: ") <= 0)
		goto err;

	if (!EVP_Digest(x->cert_info->key->public_key->data,
			x->cert_info->key->public_key->length,
			SHA1md, NULL, EVP_sha1(), NULL))
		goto err;
	for (i=0; i < SHA_DIGEST_LENGTH; i++)
		{
		if (BIO_printf(bp,"%02X",SHA1md[i]) <= 0)
			goto err;
		}
	BIO_printf(bp,"\n");

	return (1);
err:
	if (der != NULL) OPENSSL_free(der);
	return(0);
	}
