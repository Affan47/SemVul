cpor_tag_block(pdp_ctx_t *ctx, pdp_cpor_key_t *key,
                          pdp_cpor_tagdata_t* td,
                          unsigned char *block, size_t block_len,
                          int index, pdp_cpor_tag_t **t)
{
    pdp_cpor_tag_t *tag = NULL;
    pdp_cpor_ctx_t *p = NULL;
    BN_CTX *bctx = NULL;
    BIGNUM *prf_i = NULL;
    BIGNUM *message = NULL;
    BIGNUM *product = NULL;
    BIGNUM *sum = NULL;
    unsigned char *sector = NULL;
    unsigned int sector_size = 0;
    int j, status = -1;

    if (!is_cpor(ctx) || !key || !block || !block_len || !td || !t)
        return -1;
    p = ctx->cpor_param;


    if (!key->Zp || !td->alpha || !td->k_prf)
        return -1;


    if ((tag = cpor_tag_new()) == NULL) goto cleanup;
    if ((bctx = BN_CTX_new()) == NULL) goto cleanup;
    if ((message = BN_new()) == NULL) goto cleanup;
    if ((product = BN_new()) == NULL) goto cleanup;
    if ((sum = BN_new()) == NULL) goto cleanup;


    prf_i = gen_prf_k(td->k_prf, p->prf_key_size, index);
    if (prf_i == NULL) goto cleanup;


    BN_clear(sum);
    for (j=0; j< p->num_sectors; j++) {
        sector = block + (j * p->sector_size);

        sector_size = block_len - (j * p->sector_size);
        if (sector_size > p->sector_size) {
            sector_size = p->sector_size;
        }


        if (!BN_bin2bn(sector, sector_size, message)) goto cleanup;


        if (BN_ucmp(message, key->Zp) == 1) goto cleanup;


        if (!BN_mod_mul(product, td->alpha[j], message, key->Zp, bctx))
            goto cleanup;


        if (!BN_mod_add(sum, product, sum, key->Zp, bctx)) goto cleanup;
    }


    if (!BN_mod_add(tag->sigma, prf_i, sum, key->Zp, bctx)) goto cleanup;

    tag->index = index;
    *t = tag;
    status = 0;

cleanup:
    if (prf_i) BN_clear_free(prf_i);
    if (message) BN_clear_free(message);
    if (product) BN_clear_free(product);
    if (sum) BN_clear_free(sum);
    if (bctx) BN_CTX_free(bctx);
    if (status) cpor_tag_free(tag);
    return status;
}
