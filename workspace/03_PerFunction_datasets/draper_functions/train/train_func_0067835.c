rb_setup_ssl_server(const char *cert, const char *keyfile, const char *dhfile)
{
	int ret;
	gnutls_datum_t *d_cert, *d_key;
	if(cert == NULL)
	{
		rb_lib_log("rb_setup_ssl_server: No certificate file");
		return 0;
	}

	if((d_cert = rb_load_file_into_datum_t(cert)) == NULL)
	{
		rb_lib_log("rb_setup_ssl_server: Error loading certificate: %s", strerror(errno));
		return 0;
	}

	if((d_key = rb_load_file_into_datum_t(keyfile)) == NULL)
	{
		rb_lib_log("rb_setup_ssl_server: Error loading key: %s", strerror(errno));
		return 0;
	}


	gnutls_x509_privkey_init(&x509_key);
	if ((ret = gnutls_x509_privkey_import(x509_key, d_key, GNUTLS_X509_FMT_PEM)) != GNUTLS_E_SUCCESS)
	{
		rb_lib_log("rb_setup_ssl_server: Error loading key file: %s", gnutls_strerror(ret));
		return 0;
	}

	x509_cert_count = MAX_CERTS;
	if ((ret = gnutls_x509_crt_list_import(x509_cert, &x509_cert_count, d_cert, GNUTLS_X509_FMT_PEM,
		GNUTLS_X509_CRT_LIST_IMPORT_FAIL_IF_EXCEED)) < 0)
	{
		rb_lib_log("rb_setup_ssl_server: Error loading certificate: %s", gnutls_strerror(ret));
		return 0;
	}
	x509_cert_count = ret;

	if((ret =
	    gnutls_certificate_set_x509_key_mem(x509, d_cert, d_key,
						GNUTLS_X509_FMT_PEM)) != GNUTLS_E_SUCCESS)
	{
		rb_lib_log("rb_setup_ssl_server: Error loading certificate or key file: %s",
			   gnutls_strerror(ret));
		return 0;
	}

	rb_free_datum_t(d_cert);
	rb_free_datum_t(d_key);

	if(dhfile != NULL)
	{
		if(gnutls_dh_params_init(&dh_params) == GNUTLS_E_SUCCESS)
		{
			gnutls_datum_t *data;
			int xret;
			data = rb_load_file_into_datum_t(dhfile);
			if(data != NULL)
			{
				xret = gnutls_dh_params_import_pkcs3(dh_params, data,
								     GNUTLS_X509_FMT_PEM);
				if(xret < 0)
					rb_lib_log
						("rb_setup_ssl_server: Error parsing DH file: %s\n",
						 gnutls_strerror(xret));
				rb_free_datum_t(data);
			}
			gnutls_certificate_set_dh_params(x509, dh_params);
		}
		else
			rb_lib_log("rb_setup_ssl_server: Unable to setup DH parameters");
	}
	return 1;
}
