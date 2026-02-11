sslHandshake(_mhClientCtx_t *cctx)
{
    sslCtx_t *ssl_ctx = cctx->ssl_ctx;
    int result;

    if (ssl_ctx->renegotiate) {
        if (!SSL_do_handshake(ssl_ctx->ssl))
            return APR_EGENERAL;
    }

    if (ssl_ctx->handshake_done)
        return APR_SUCCESS;


    result = SSL_accept(ssl_ctx->ssl);
    if (result == 1) {
        _mhLog(MH_VERBOSE, cctx->skt, "Handshake successful.\n");
        ssl_ctx->handshake_done = YES;

        return APR_SUCCESS;
    } else {
        int ssl_err;

        ssl_err = SSL_get_error(ssl_ctx->ssl, result);
        switch (ssl_err) {
            case SSL_ERROR_WANT_READ:
            case SSL_ERROR_WANT_WRITE:
                return APR_EAGAIN;
            case SSL_ERROR_SYSCALL:
                return ssl_ctx->bio_read_status;
            default:
                _mhLog(MH_VERBOSE, cctx->skt, "SSL Error %d: ", ssl_err);
#if MH_VERBOSE
                ERR_print_errors_fp(stderr);
#endif
                return APR_EGENERAL;
        }
    }


    return APR_EGENERAL;
}
