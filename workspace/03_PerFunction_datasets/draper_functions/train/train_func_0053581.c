git_openssl_stream_new(git_stream **out, const char *host, const char *port)
{
	openssl_stream *st;

	st = git__calloc(1, sizeof(openssl_stream));
	GITERR_CHECK_ALLOC(st);

	if (git_socket_stream_new((git_stream **) &st->socket, host, port))
		return -1;

	st->ssl = SSL_new(git__ssl_ctx);
	if (st->ssl == NULL) {
		giterr_set(GITERR_SSL, "failed to create ssl object");
		return -1;
	}

	st->parent.version = GIT_STREAM_VERSION;
	st->parent.encrypted = 1;
	st->parent.connect = openssl_connect;
	st->parent.certificate = openssl_certificate;
	st->parent.read = openssl_read;
	st->parent.write = openssl_write;
	st->parent.close = openssl_close;
	st->parent.free = openssl_free;

	*out = (git_stream *) st;
	return 0;
}
