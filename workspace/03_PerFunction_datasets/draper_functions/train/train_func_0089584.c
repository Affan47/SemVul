canonicalize_user(struct webauth_context *ctx, struct webauth_krb5 *kc,
                  const char **result)
{
    enum webauth_krb5_canon canonicalize;
    const char *local;
    char *subject;
    int s;


    *result = NULL;


    if (apr_is_empty_array(ctx->webkdc->local_realms))
        canonicalize = WA_KRB5_CANON_LOCAL;
    else {
        local = APR_ARRAY_IDX(ctx->webkdc->local_realms, 0, const char *);
        if (strcmp(local, "none") == 0)
            canonicalize = WA_KRB5_CANON_NONE;
        else if (strcmp(local, "local") == 0)
            canonicalize = WA_KRB5_CANON_LOCAL;
        else
            canonicalize = is_local_realm(ctx, kc);
    }


    s = webauth_krb5_get_principal(ctx, kc, &subject, canonicalize);
    if (s != WA_ERR_NONE)
        return s;
    *result = apr_pstrdup(ctx->pool, subject);
    return WA_ERR_NONE;
}
