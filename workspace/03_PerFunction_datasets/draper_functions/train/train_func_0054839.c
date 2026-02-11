ssl_certificate_get_x509_and_pkey_from_p12_file(const gchar *file, const gchar *password,
			gnutls_x509_crt_t *x509, gnutls_x509_privkey_t *pkey)
{
	gnutls_pkcs12_t p12 = NULL;

	int r;

	*x509 = NULL;
	*pkey = NULL;
	if (!file)
		return;

	if (is_file_exist(file)) {
		FILE *fp = g_fopen(file, "r");
		if (fp) {
			p12 = gnutls_d2i_PKCS12_fp(fp, 0);
			fclose(fp);
			if (!p12) {
				log_error(LOG_PROTOCOL, _("Failed to read P12 certificate file %s\n"), file);
			}
		} else {
			log_error(LOG_PROTOCOL, _("Cannot open P12 certificate file %s (%s)\n"),
				  file, strerror(errno));
		}
	} else {
		log_error(LOG_PROTOCOL, _("P12 Certificate file %s missing (%s)\n"), file,
			  strerror(errno));
	}
	if (p12 != NULL) {
		if ((r = parse_pkcs12(p12, password, pkey, x509)) == 0) {
			debug_print("got p12\n");
		} else {
			log_error(LOG_PROTOCOL, "%s\n", gnutls_strerror(r));
		}
		gnutls_pkcs12_deinit(p12);
	}
}
