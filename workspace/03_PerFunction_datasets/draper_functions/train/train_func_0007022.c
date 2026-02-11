arc4_gen_keystream(void *ctx_, size_t offset, uint8_t *obuf, size_t olen)
{
    arc4_context *ctx = ctx_;
    int x, y, a, b;
    size_t i;
    uint8_t *m;

    x = ctx->x;
    y = ctx->y;
    m = ctx->m;

    if (offset < ctx->offset)
        abort();

    for (i = ctx->offset; i < offset; i++)
        ARC4_ROUND(x, y, a, b, m);

    for (i = 0; i < olen; i++)
    {
        ARC4_ROUND(x, y, a, b, m);
        obuf[i] = (uint8_t) m[(uint8_t)(a + b)];
    }

    ctx->x = x;
    ctx->y = y;
    ctx->offset = offset + olen;
}
