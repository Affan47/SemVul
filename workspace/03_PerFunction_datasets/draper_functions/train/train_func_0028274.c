apdp_key_free(const pdp_ctx_t *ctx, pdp_key_t *k)
{
    pdp_apdp_key_t *key = NULL;
    pdp_apdp_ctx_t *p = NULL;

    if (!k || !k->apdp)
        return -1;
    p = ctx->apdp_param;
    key = k->apdp;

    if (key->rsa) RSA_free(key->rsa);
    if (key->g) BN_clear_free(key->g);
    sfree(key->v, p->prf_key_size);
    sfree(key, sizeof(pdp_apdp_key_t));
    CRYPTO_cleanup_all_ex_data();
    return 0;
}
