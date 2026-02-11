readFromSocket(bucket_t *bkt)
{
    _bufferedSocketCtx_t *ctx = bkt->data;
    apr_status_t status;


    apr_size_t len = BUFSIZE - ctx->remaining;

    if (len == 0)
        return APR_EAGAIN;

    STATUSREADERR(ctx->read(ctx->skt, ctx->read_baton,
                            ctx->buf + ctx->remaining, &len));
    if (len) {
        _mhLog(MH_VERBOSE, ctx->skt,
               "recvd with status %d:\n%.*s\n---- %d ----\n",
               status, (unsigned int)len, ctx->buf + ctx->remaining,
               (unsigned int)len);
        ctx->remaining += len;
    }
    return status;
}
