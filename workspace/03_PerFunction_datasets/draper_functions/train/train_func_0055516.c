macpdp_proof_free(const pdp_ctx_t *ctx, pdp_macpdp_proof_t *proof)
{
    if (!is_macpdp(ctx) || !proof || !proof->ell)
        return -1;

    sfree(proof->B, proof->ell * ctx->macpdp_param->block_size);
    sfree(proof->T, proof->ell * ctx->macpdp_param->tag_size);
    proof->ell = 0;
    return 0;
}
