__rfbssl_read(rfbClientPtr cl, char *buf, int bufsize, int peek)
{
    int ret = 0;
    struct rfbssl_ctx *ctx = (struct rfbssl_ctx *)cl->sslctx;

    rfbssl_gc_peekbuf(ctx, bufsize);

    if (ctx->peeklen) {

	ret = bufsize < ctx->peeklen ? bufsize : ctx->peeklen;
	memcpy (buf, ctx->peekbuf + ctx->peekstart, ret);
	if (!peek) {
	    ctx->peeklen -= ret;
	    if (ctx->peeklen != 0)
		ctx->peekstart += ret;
	    else
		ctx->peekstart = 0;
	}
    }

    if (ret < bufsize) {
	int n;

	if ((n = rfbssl_do_read(cl, buf + ret, bufsize - ret)) <= 0) {
	    rfbErr("rfbssl_%s: %s error\n", __func__, peek ? "peek" : "read");
	    return n;
	}
	if (peek) {
	    memcpy(ctx->peekbuf + ctx->peekstart + ctx->peeklen, buf + ret, n);
	    ctx->peeklen += n;
	}
	ret += n;
    }

    return ret;
}
