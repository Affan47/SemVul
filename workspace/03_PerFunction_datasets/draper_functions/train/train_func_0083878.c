duo_reset(struct duo_ctx *ctx)
{
    int i;

    for (i = 0; i < ctx->argc; i++) {
            free(ctx->argv[i]);
            ctx->argv[i] = NULL;
    }
    ctx->argc = 0;
    *ctx->err = '\0';

    return (DUO_OK);
}
