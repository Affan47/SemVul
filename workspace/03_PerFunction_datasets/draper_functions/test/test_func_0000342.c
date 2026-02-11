http_connect(http_subtransport *t)
{
	int flags = 0, error;

	if (t->connected &&
		http_should_keep_alive(&t->parser) &&
		t->parse_finished)
		return 0;

	if (t->socket.socket)
		gitno_close(&t->socket);

	if (t->connection_data.use_ssl) {
		int tflags;

		if (t->owner->parent.read_flags(&t->owner->parent, &tflags) < 0)
			return -1;

		flags |= GITNO_CONNECT_SSL;
	}

	error = gitno_connect(&t->socket, t->connection_data.host, t->connection_data.port, flags);

#ifdef GIT_SSL
	if ((!error || error == GIT_ECERTIFICATE) && t->owner->certificate_check_cb != NULL) {
                X509 *cert = SSL_get_peer_certificate(t->socket.ssl.ssl);
		git_cert_x509 cert_info, *cert_info_ptr;
                int len, is_valid;
		unsigned char *guard, *encoded_cert;


		len = i2d_X509(cert, NULL);
		if (len < 0) {
			giterr_set(GITERR_NET, "failed to retrieve certificate information");
			return -1;
		}


		encoded_cert = git__malloc(len);
		GITERR_CHECK_ALLOC(encoded_cert);

		guard = encoded_cert;

		len = i2d_X509(cert, &guard);
		if (len < 0) {
			git__free(encoded_cert);
			giterr_set(GITERR_NET, "failed to retrieve certificate information");
			return -1;
		}

		giterr_clear();
		is_valid = error != GIT_ECERTIFICATE;
		cert_info.cert_type = GIT_CERT_X509;
		cert_info.data = encoded_cert;
		cert_info.len = len;

		cert_info_ptr = &cert_info;

		error = t->owner->certificate_check_cb((git_cert *) cert_info_ptr, is_valid, t->connection_data.host, t->owner->message_cb_payload);
		git__free(encoded_cert);

		if (error < 0) {
			if (!giterr_last())
				giterr_set(GITERR_NET, "user cancelled certificate check");

			return error;
		}
	}
#endif
	if (error < 0)
		return error;

	t->connected = 1;
	return 0;
}
