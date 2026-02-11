ossl_ssl_session_get_id(VALUE self)
{
	SSL_SESSION *ctx;
	const unsigned char *p = NULL;
	unsigned int i = 0;

	GetSSLSession(self, ctx);

	p = SSL_SESSION_get_id(ctx, &i);

	return rb_str_new((const char *) p, i);
}
