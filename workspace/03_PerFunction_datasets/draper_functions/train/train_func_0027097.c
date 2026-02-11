rfbssl_do_read(rfbClientPtr cl, char *buf, int bufsize)
{
    struct rfbssl_ctx *ctx = (struct rfbssl_ctx *)cl->sslctx;
    int ret;

    while ((ret = gnutls_record_recv(ctx->session, buf, bufsize)) < 0) {
	if (ret == GNUTLS_E_AGAIN) {

	} else if (ret == GNUTLS_E_INTERRUPTED) {

	} else {
	    break;
	}
    }

    if (ret < 0) {
	rfbssl_error(__func__, ret);
	errno = EIO;
	ret = -1;
    }

    return ret < 0 ? -1 : ret;
}
