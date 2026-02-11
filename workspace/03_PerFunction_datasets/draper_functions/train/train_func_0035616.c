ossl_ssl_close(VALUE self)
{
    SSL *ssl;

    Data_Get_Struct(self, SSL, ssl);
    if (ssl) {
	VALUE io = ossl_ssl_get_io(self);
	if (!RTEST(rb_funcall(io, rb_intern("closed?"), 0))) {
	    ossl_ssl_shutdown(ssl);
	    SSL_free(ssl);
	    DATA_PTR(self) = NULL;
	    if (RTEST(ossl_ssl_get_sync_close(self)))
		rb_funcall(io, rb_intern("close"), 0);
	}
    }

    return Qnil;
}
