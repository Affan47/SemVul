cpor_key_open(const pdp_ctx_t *ctx, pdp_key_t *k, pdp_key_t *pub,
                  const char* path)
{
    char pri_keypath[MAXPATHLEN];
    char pub_keypath[MAXPATHLEN];
    int err = -1;

    if (!is_cpor(ctx) || !path || (strlen(path) > MAXPATHLEN))
        return -1;


    err = get_key_paths(pri_keypath, sizeof(pri_keypath),
                        pub_keypath, sizeof(pub_keypath), path, "cpor");
    if (err) goto cleanup;
    if (access(pri_keypath, F_OK) && access(pub_keypath, F_OK)) goto cleanup;

    if (k) {
        err = cpor_pri_key_open(ctx, k, pri_keypath);
        if (err) goto cleanup;
    }
    if (pub) {
        err = cpor_pub_key_open(ctx, pub, pub_keypath);
        if (err) goto cleanup;
    }
    return 0;

cleanup:
    cpor_key_free(ctx, k);
    cpor_key_free(ctx, pub);
    return -1;
}
