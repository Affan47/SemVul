MD5Update(struct MD5Context *ctx, unsigned char *buf, unsigned len)
{
    uint32_t t;


    t = ctx->bits[0];
    if ((ctx->bits[0] = t + ((uint32_t) len << 3)) < t)
        ctx->bits[1]++;
    ctx->bits[1] += len >> 29;

    t = (t >> 3) & 0x3f;


    if (t) {
        unsigned char *p = (unsigned char *) ctx->in + t;

        t = 64 - t;
        if (len < t) {
            memcpy(p, buf, len);
            return;
        }
        memcpy(p, buf, t);
        byteReverse(ctx->in, 16);
        MD5Transform(ctx->buf, (uint32_t *) ctx->in);
        buf += t;
        len -= t;
    }


    while (len >= 64) {
        memcpy(ctx->in, buf, 64);
        byteReverse(ctx->in, 16);
        MD5Transform(ctx->buf, (uint32_t *) ctx->in);
        buf += 64;
        len -= 64;
    }


    memcpy(ctx->in, buf, len);
}
