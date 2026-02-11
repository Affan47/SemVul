apdp_ctx_free(pdp_ctx_t *ctx)
{
    if (!ctx) return -1;
    sfree(ctx->apdp_param, sizeof(pdp_apdp_ctx_t));
    return 0;
}
