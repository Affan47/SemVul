webauth_krb5_import_cred(struct webauth_context *ctx, struct webauth_krb5 *kc,
                         const void *cred, size_t cred_len, const char *cache)
{
    krb5_creds creds;
    krb5_error_code code;
    int s;


    s = decode_creds(ctx, kc, cred, cred_len, &creds);
    if (s != WA_ERR_NONE)
        return s;


    if (kc->cc == NULL) {
        s = prepare_from_creds(ctx, kc, &creds, cache);
        if (s != WA_ERR_NONE)
            return s;
    }


    code = krb5_cc_store_cred(kc->ctx, kc->cc, &creds);
    if (creds.client != NULL)
        krb5_free_principal(kc->ctx, creds.client);
    if (creds.server != NULL)
        krb5_free_principal(kc->ctx, creds.server);
    if (code != 0)
        return error_set(ctx, kc, code, "cannot store credentials in cache");
    return WA_ERR_NONE;
}
