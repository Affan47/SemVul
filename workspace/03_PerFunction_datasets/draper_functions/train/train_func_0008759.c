_crywrap_tls_session_create(const crywrap_config_t * config)
{
	gnutls_session_t session;
	int ret;

	gnutls_init(&session, GNUTLS_SERVER);

	if (config->anon) {
		gnutls_credentials_set(session, GNUTLS_CRD_ANON, cred);
	} else {
		gnutls_credentials_set(session, GNUTLS_CRD_CERTIFICATE,
				       cred);
	}

	ret = gnutls_priority_set(session, config->priority);
	if (ret < 0) {
		cry_error("Error setting priority %s: ",
			  gnutls_strerror(ret));
		exit(4);
	}

	if (config->verify == 1)
		gnutls_certificate_server_set_request(session,
						      GNUTLS_CERT_REQUEST);
	else if (config->verify == 2)
		gnutls_certificate_server_set_request(session,
						      GNUTLS_CERT_REQUIRE);

	return session;
}
