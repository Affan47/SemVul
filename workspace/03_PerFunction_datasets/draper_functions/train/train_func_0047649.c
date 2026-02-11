pbkdf2_string_to_key(const struct krb5_keytypes *ktp, const krb5_data *string,
                     const krb5_data *salt, const krb5_data *pepper,
                     const krb5_data *params, krb5_keyblock *key,
                     enum deriv_alg deriv_alg, unsigned long def_iter_count)
{
    unsigned long iter_count;
    krb5_data out;
    static const krb5_data usage = { KV5M_DATA, 8, "kerberos" };
    krb5_key tempkey = NULL;
    krb5_error_code err;
    krb5_data sandp = empty_data();

    if (params) {
        unsigned char *p = (unsigned char *) params->data;
        if (params->length != 4)
            return KRB5_ERR_BAD_S2K_PARAMS;

        iter_count = load_32_be(p);
        if (iter_count == 0) {
            iter_count = (1UL << 16) << 16;
            if (((iter_count >> 16) >> 16) != 1)
                return KRB5_ERR_BAD_S2K_PARAMS;
        }
        if (!k5_allow_weak_pbkdf2iter && iter_count < def_iter_count)
            return KRB5_ERR_BAD_S2K_PARAMS;

    } else
        iter_count = def_iter_count;


    if (iter_count >= MAX_ITERATION_COUNT)
        return KRB5_ERR_BAD_S2K_PARAMS;


    out.data = (char *) key->contents;
    out.length = key->length;
    if (out.length != 16 && out.length != 32)
        return KRB5_CRYPTO_INTERNAL;

    if (pepper != NULL) {
        err = alloc_data(&sandp, pepper->length + 1 + salt->length);
        if (err)
            return err;

        if (pepper->length > 0)
            memcpy(sandp.data, pepper->data, pepper->length);
        sandp.data[pepper->length] = '\0';
        if (salt->length > 0)
            memcpy(&sandp.data[pepper->length + 1], salt->data, salt->length);

        salt = &sandp;
    }

    err = krb5int_pbkdf2_hmac_sha1 (&out, iter_count, string, salt);
    if (err)
        goto cleanup;

    err = krb5_k_create_key (NULL, key, &tempkey);
    if (err)
        goto cleanup;

    err = krb5int_derive_keyblock(ktp->enc, tempkey, key, &usage, deriv_alg);

cleanup:
    if (sandp.data)
        free(sandp.data);
    if (err)
        memset (out.data, 0, out.length);
    krb5_k_free_key (NULL, tempkey);
    return err;
}
