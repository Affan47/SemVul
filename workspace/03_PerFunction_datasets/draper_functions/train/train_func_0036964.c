load_one_ca_file(const char *path, crypto_error **error)
{
	gnutls_x509_crt_t *list = NULL;
	gnutls_x509_crt_t cert;
	gnutls_datum dt;
	size_t fsize = 0;
	int err;

	dt.data = crypto_read_file(path, &fsize, error);
	if (!dt.data)
		return NULL;

	dt.size = (unsigned int) fsize;
	if (gnutls_x509_crt_init (&cert) != GNUTLS_E_SUCCESS) {
		gnutls_free(dt.data);
		crypto_error_set(error, 1, ENOMEM, "not enough memory for certificate");
		goto out;
	}

	err = gnutls_x509_crt_import (cert, &dt, GNUTLS_X509_FMT_PEM);
	if (err != GNUTLS_E_SUCCESS)
		err = gnutls_x509_crt_import (cert, &dt, GNUTLS_X509_FMT_DER);
	gnutls_free(dt.data);
	if (err != GNUTLS_E_SUCCESS) {
		crypto_error_set(error, 1, 0, "certificate (%s) format unknown", path);
		goto out;
	}

	list = gnutls_malloc(sizeof(gnutls_x509_crt_t));
	if (!list) {
		crypto_error_set(error, 1, ENOMEM, "not enough memory for certificate list");
		goto out;
	} else
		list[0] = cert;

out:
	gnutls_x509_crt_deinit (cert);
	return list;
}
