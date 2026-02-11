openssl_certificate(git_cert **out, git_stream *stream)
{
	openssl_stream *st = (openssl_stream *) stream;
	int len;
	X509 *cert = SSL_get_peer_certificate(st->ssl);
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

	st->cert_info.cert_type = GIT_CERT_X509;
	st->cert_info.data = encoded_cert;
	st->cert_info.len = len;

	*out = (git_cert *)&st->cert_info;
	return 0;
}
