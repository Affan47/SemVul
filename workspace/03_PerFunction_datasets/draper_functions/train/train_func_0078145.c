ossl_spki_print(VALUE self)
{
    NETSCAPE_SPKI *spki;
    BIO *out;
    BUF_MEM *buf;
    VALUE str;

    GetSPKI(self, spki);
    if (!(out = BIO_new(BIO_s_mem()))) {
	ossl_raise(eSPKIError, NULL);
    }
    if (!NETSCAPE_SPKI_print(out, spki)) {
	BIO_free(out);
	ossl_raise(eSPKIError, NULL);
    }
    BIO_get_mem_ptr(out, &buf);
    str = rb_str_new(buf->data, buf->length);
    BIO_free(out);

    return str;
}
