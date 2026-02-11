switch_to_anon_dh(void) {
	long mode;

	rfbLog("Using Anonymous Diffie-Hellman mode.\n");
	rfbLog("WARNING: Anonymous Diffie-Hellman uses encryption but is\n");
	rfbLog("WARNING: susceptible to a Man-In-The-Middle attack.\n");
	if (ssl_client_mode) {
		ctx = SSL_CTX_new( SSLv23_client_method() );
	} else {
		ctx = SSL_CTX_new( SSLv23_server_method() );
	}
	if (ctx == NULL) {
		return 0;
	}
	if (ssl_client_mode) {
		return 1;
	}
	if (!SSL_CTX_set_cipher_list(ctx, "ADH:@STRENGTH")) {
		return 0;
	}
	if (!add_anon_dh()) {
		return 0;
	}

	mode = 0;
	mode |= SSL_MODE_ENABLE_PARTIAL_WRITE;
	mode |= SSL_MODE_ACCEPT_MOVING_WRITE_BUFFER;
	SSL_CTX_set_mode(ctx, mode);

	SSL_CTX_set_session_cache_mode(ctx, SSL_SESS_CACHE_BOTH);
	SSL_CTX_set_timeout(ctx, 300);
	SSL_CTX_set_default_passwd_cb(ctx, pem_passwd_callback);
	SSL_CTX_set_verify(ctx, SSL_VERIFY_NONE, NULL);

	return 1;
}
