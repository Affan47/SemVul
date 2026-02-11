ossl_x509stctx_get_curr_cert(VALUE self)
{
    X509_STORE_CTX *ctx;

    GetX509StCtx(self, ctx);

    return ossl_x509_new(X509_STORE_CTX_get_current_cert(ctx));
}
