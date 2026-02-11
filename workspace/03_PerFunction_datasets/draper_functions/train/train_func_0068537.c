ossl_ssl_get_cipher(VALUE self)
{
    SSL *ssl;
    SSL_CIPHER *cipher;

    Data_Get_Struct(self, SSL, ssl);
    if (!ssl) {
        rb_warning("SSL session is not started yet.");
        return Qnil;
    }
    cipher = (SSL_CIPHER *)SSL_get_current_cipher(ssl);

    return ossl_ssl_cipher_to_ary(cipher);
}
