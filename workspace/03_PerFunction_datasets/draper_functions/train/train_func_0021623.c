add_cert(SSL_CTX *ssl_ctx, const uint8_t *buf, int len)
{
    int ret = SSL_ERROR_NO_CERT_DEFINED, i = 0;
    SSL_CERT *ssl_cert;
    X509_CTX *cert = NULL;
    int offset;

    while (ssl_ctx->certs[i].buf && i < CONFIG_SSL_MAX_CERTS)
        i++;

    if (i == CONFIG_SSL_MAX_CERTS)
    {
#ifdef CONFIG_SSL_FULL_MODE
        printf("Error: maximum number of certs added (%d) - change of "
                "compile-time configuration required\n",
                CONFIG_SSL_MAX_CERTS);
#endif
        goto error;
    }

    if ((ret = x509_new(buf, &offset, &cert)))
        goto error;

#if defined (CONFIG_SSL_FULL_MODE)
    if (ssl_ctx->options & SSL_DISPLAY_CERTS)
        x509_print(cert, NULL);
#endif

    ssl_cert = &ssl_ctx->certs[i];
    ssl_cert->size = len;
    ssl_cert->buf = (uint8_t *)malloc(len);
    memcpy(ssl_cert->buf, buf, len);
    ssl_ctx->chain_length++;
    len -= offset;
    ret = SSL_OK;


    if (len > 0)
    {
        ret = add_cert(ssl_ctx, &buf[offset], len);
    }

error:
    x509_free(cert);
    return ret;
}
