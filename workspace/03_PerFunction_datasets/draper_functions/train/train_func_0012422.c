buffSktRead(bucket_t *bkt, apr_size_t requested,
                                const char **data, apr_size_t *len)
{
    _bufferedSocketCtx_t *ctx = bkt->data;
    apr_status_t status;


    if (ctx->offset > 0) {
        memmove(ctx->buf, ctx->buf + ctx->offset, BUFSIZE - ctx->offset);
        ctx->offset = 0;
    }

    status = readFromSocket(bkt);


    *len = ctx->remaining <= requested ? ctx->remaining : requested;
    *data = ctx->buf;

    ctx->offset += *len;
    ctx->remaining -= *len;

    if (ctx->remaining > 0)
        return APR_SUCCESS;

    return status;
}
