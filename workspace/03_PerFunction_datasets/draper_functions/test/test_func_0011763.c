ossl_ssl_session_get_time(VALUE self)
{
	SSL_SESSION *ctx;
	time_t t;

	GetSSLSession(self, ctx);

	t = SSL_SESSION_get_time(ctx);

	if (t == 0)
		return Qnil;

	return rb_funcall(rb_cTime, rb_intern("at"), 1, TIMET2NUM(t));
}
