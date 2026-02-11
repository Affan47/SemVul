openssl_connect(git_stream *stream)
{
	int ret;
	openssl_stream *st = (openssl_stream *) stream;

	if ((ret = git_stream_connect((git_stream *)st->socket)) < 0)
		return ret;

	if ((ret = SSL_set_fd(st->ssl, st->socket->s)) <= 0) {
		openssl_close((git_stream *) st);
		return ssl_set_error(st->ssl, ret);
	}

	if ((ret = SSL_connect(st->ssl)) <= 0)
		return ssl_set_error(st->ssl, ret);

	return verify_server_cert(st->ssl, st->socket->host);
}
