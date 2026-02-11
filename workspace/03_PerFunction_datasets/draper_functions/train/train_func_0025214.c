get_subject(MWK_REQ_CTXT *rc, struct webauth_krb5 *kc,
            char **subject, const char *mwk_func)
{
    enum webauth_krb5_canon canonicalize = WA_KRB5_CANON_LOCAL;
    int status;


    if (rc->sconf->local_realms->nelts > 0) {
        apr_array_header_t *realms;
        char *realm;
        char **local;

        realms = apr_array_copy(rc->r->pool, rc->sconf->local_realms);
        local = apr_array_pop(realms);
        if (apr_strnatcmp(*local, "none") == 0) {
            canonicalize = WA_KRB5_CANON_NONE;
        } else if (apr_strnatcmp(*local, "local") == 0) {
            canonicalize = WA_KRB5_CANON_LOCAL;
        } else {
            canonicalize = WA_KRB5_CANON_NONE;
            status = webauth_krb5_get_realm(rc->ctx, kc, &realm);
            if (status != WA_ERR_NONE) {
                char *msg = mwk_webauth_error_message(rc->ctx, rc->r, status,
                                                      "webauth_krb5_get_realm",
                                                      NULL);
                set_errorResponse(rc, WA_PEC_SERVER_FAILURE, msg, mwk_func,
                                  true);
                return MWK_ERROR;
            }
            do {
                if (apr_strnatcmp(*local, realm) == 0)
                    canonicalize = WA_KRB5_CANON_STRIP;
            } while ((local = apr_array_pop(realms)) != NULL);
        }
    }


    status = webauth_krb5_get_principal(rc->ctx, kc, subject, canonicalize);
    if (status != WA_ERR_NONE) {
        char *msg = mwk_webauth_error_message(rc->ctx, rc->r, status,
                                             "webauth_krb5_get_principal",
                                              NULL);
        set_errorResponse(rc, WA_PEC_SERVER_FAILURE, msg, mwk_func, true);
        return MWK_ERROR;
    }
    return MWK_OK;
}
