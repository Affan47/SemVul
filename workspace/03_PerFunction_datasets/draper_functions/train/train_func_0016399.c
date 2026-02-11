callb(int ok, X509_STORE_CTX *ctx)
	{
	int err;
	X509 *err_cert;


	err=X509_STORE_CTX_get_error(ctx);
	if (err == X509_V_ERR_DEPTH_ZERO_SELF_SIGNED_CERT)
		return 1;


	if (ok)
		{
		BIO_printf(bio_err,"error with certificate to be certified - should be self signed\n");
		return 0;
		}
	else
		{
		err_cert=X509_STORE_CTX_get_current_cert(ctx);
		print_name(bio_err, NULL, X509_get_subject_name(err_cert),0);
		BIO_printf(bio_err,"error with certificate - error %d at depth %d\n%s\n",
			err,X509_STORE_CTX_get_error_depth(ctx),
			X509_verify_cert_error_string(err));
		return 1;
		}
	}
