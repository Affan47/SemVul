apdp_pub_key_open(const pdp_ctx_t *ctx, pdp_key_t *k,
                             const char* pub_keypath)
{
    int status = -1;
    size_t gen_len;
    FILE *pub_key = NULL;
    unsigned char *gen = NULL;
    pdp_apdp_key_t *key = NULL;

    if (!is_apdp(ctx) || !k || !pub_keypath) return -1;
    if (strlen(pub_keypath) > MAXPATHLEN) return -1;

    if ((key = malloc(sizeof(pdp_apdp_key_t))) == NULL) goto cleanup;
    memset(key, 0, sizeof(pdp_apdp_key_t));
    k->apdp = key;


    if ((key->g = BN_new()) == NULL) goto cleanup;


    if ((pub_key = fopen(pub_keypath, "r")) == NULL) goto cleanup;


    key->rsa = PEM_read_RSAPublicKey(pub_key, NULL, NULL, NULL);
    if (key->rsa == NULL) goto cleanup;
    if (!key->rsa->n || !key->rsa->e) goto cleanup;


    fread(&gen_len, sizeof(gen_len), 1, pub_key);
    if (ferror(pub_key)) goto cleanup;
    if ((gen = malloc(gen_len)) == NULL) goto cleanup;
    fread(gen, gen_len, 1, pub_key);
    if (ferror(pub_key)) goto cleanup;


    if (!BN_bin2bn(gen, gen_len, key->g)) goto cleanup;

    status = 0;

cleanup:
    CRYPTO_cleanup_all_ex_data();
    if (pub_key) fclose(pub_key);
    sfree(gen, gen_len);
    if (status) {
        PDP_ERR("Couldn't open key file.");
        apdp_key_free(ctx, k);
    }
    return status;
}
