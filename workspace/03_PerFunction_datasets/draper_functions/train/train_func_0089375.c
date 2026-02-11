openssl_read(git_stream *stream, void *data, size_t len)
{
	openssl_stream *st = (openssl_stream *) stream;
	int ret;

	do {
		ret = SSL_read(st->ssl, data, len);
	} while (SSL_get_error(st->ssl, ret) == SSL_ERROR_WANT_READ);

	if (ret < 0) {
		ssl_set_error(st->ssl, ret);
		return -1;
	}

	return ret;
}
