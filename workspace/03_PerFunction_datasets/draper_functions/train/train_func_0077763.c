tls_cert_check_issuer (const gchar *cert_pem, const gchar *ca_pem)
{
	gnutls_datum_t pem_datum;
        gnutls_x509_crt_t crt;
        gnutls_x509_crt_t ca_crt;
        gboolean result = FALSE;

	if (gnutls_x509_crt_init (&crt) < 0) {
		return FALSE;
	}

        pem_datum.data = (unsigned char *) cert_pem;
        pem_datum.size = strlen(cert_pem);

	if (gnutls_x509_crt_import (crt, &pem_datum, GNUTLS_X509_FMT_PEM) < 0) {
                gnutls_x509_crt_deinit (crt);
		return FALSE;
	}

	if (gnutls_x509_crt_init (&ca_crt) < 0) {
                gnutls_x509_crt_deinit (crt);
		return FALSE;
	}

        pem_datum.data = (unsigned char *) ca_pem;
        pem_datum.size = strlen(ca_pem);

	if (gnutls_x509_crt_import (ca_crt, &pem_datum, GNUTLS_X509_FMT_PEM) < 0) {
                gnutls_x509_crt_deinit (crt);
                gnutls_x509_crt_deinit (ca_crt);
		return FALSE;
	}

        result = gnutls_x509_crt_check_issuer(crt, ca_crt);
        gnutls_x509_crt_deinit (crt);
        gnutls_x509_crt_deinit (ca_crt);

        return result;
}
