get_inflate(struct cli_bc_ctx *ctx, int32_t id)
{
    if (id < 0 || (unsigned int)id >= ctx->ninflates || !ctx->inflates)
        return NULL;
    return &ctx->inflates[id];
}
