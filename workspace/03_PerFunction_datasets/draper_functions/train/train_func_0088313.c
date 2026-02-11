add_certs_from_file(STACK_OF(X509) *stack, char *certfile)
	{
	BIO *in=NULL;
	int count=0;
	int ret= -1;
	STACK_OF(X509_INFO) *sk=NULL;
	X509_INFO *xi;

	in=BIO_new(BIO_s_file());
	if ((in == NULL) || (BIO_read_filename(in,certfile) <= 0))
		{
		BIO_printf(bio_err,"error opening the file, %s\n",certfile);
		goto end;
		}


	sk=PEM_X509_INFO_read_bio(in,NULL,NULL,NULL);
	if (sk == NULL) {
		BIO_printf(bio_err,"error reading the file, %s\n",certfile);
		goto end;
	}


	while (sk_X509_INFO_num(sk))
		{
		xi=sk_X509_INFO_shift(sk);
		if (xi->x509 != NULL)
			{
			sk_X509_push(stack,xi->x509);
			xi->x509=NULL;
			count++;
			}
		X509_INFO_free(xi);
		}

	ret=count;
end:

	if (in != NULL) BIO_free(in);
	if (sk != NULL) sk_X509_INFO_free(sk);
	return(ret);
	}
