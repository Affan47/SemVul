bio_apr_socket_read(BIO *bio, char *in, int inlen)
{
    apr_size_t len = inlen;
    _mhClientCtx_t *cctx = bio->ptr;
    sslCtx_t *ssl_ctx = cctx->ssl_ctx;
    apr_status_t status;

    BIO_clear_retry_flags(bio);

    status = apr_socket_recv(cctx->skt, in, &len);
    ssl_ctx->bio_read_status = status;

    if (len || status != APR_EAGAIN)
        _mhLog(MH_VERBOSE, cctx->skt, "Read %d bytes from ssl socket with "
               "status %d.\n", len, status);

    if (status == APR_EAGAIN) {
        BIO_set_retry_read(bio);
        if (len == 0)
            return -1;
    }

    if (READ_ERROR(status))
        return -1;

    return len;
}
