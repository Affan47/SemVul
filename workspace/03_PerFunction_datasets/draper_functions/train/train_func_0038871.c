xmlSecOpenSSLKeyDataX509Finalize(xmlSecKeyDataPtr data) {
    xmlSecOpenSSLX509DataCtxPtr ctx;

    xmlSecAssert(xmlSecKeyDataCheckId(data, xmlSecOpenSSLKeyDataX509Id));

    ctx = xmlSecOpenSSLX509DataGetCtx(data);
    xmlSecAssert(ctx != NULL);

    if(ctx->certsList != NULL) {
        sk_X509_pop_free(ctx->certsList, X509_free);
    }
    if(ctx->crlsList != NULL) {
        sk_X509_CRL_pop_free(ctx->crlsList, X509_CRL_free);
    }
    if(ctx->keyCert != NULL) {
        X509_free(ctx->keyCert);
    }
    memset(ctx, 0, sizeof(xmlSecOpenSSLX509DataCtx));
}
