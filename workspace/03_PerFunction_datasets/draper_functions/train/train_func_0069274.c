make_app_cookie(const char *subject,
                const char *authz_subject,
                time_t creation_time,
                time_t expiration_time,
                time_t last_used_time,
                const char *initial_factors,
                const char *session_factors,
                uint32_t loa,
                MWA_REQ_CTXT *rc)
{
    const char *mwa_func = "make_app_cookie";
    struct webauth_token *data;
    struct webauth_token_app *app;
    const char *token;
    int status;

    if (rc->sconf->ring == NULL)
        return 0;
    if (creation_time == 0) {
        creation_time = time(NULL);
        if (rc->dconf->app_token_lifetime)
            expiration_time = creation_time + rc->dconf->app_token_lifetime;
        last_used_time =
            rc->dconf->last_use_update_interval ? creation_time : 0;
    }
    data = apr_pcalloc(rc->r->pool, sizeof(struct webauth_token));
    data->type = WA_TOKEN_APP;
    app = &data->token.app;
    app->subject = apr_pstrdup(rc->r->pool, subject);
    if (authz_subject != NULL)
        app->authz_subject = apr_pstrdup(rc->r->pool, authz_subject);
    app->last_used = last_used_time;
    if (initial_factors != NULL)
        app->initial_factors = apr_pstrdup(rc->r->pool, initial_factors);
    if (session_factors != NULL)
        app->session_factors = apr_pstrdup(rc->r->pool, session_factors);
    app->loa = loa;
    app->creation = creation_time;
    app->expiration = expiration_time;
    status = webauth_token_encode(rc->ctx, data, rc->sconf->ring, &token);
    if (status != WA_ERR_NONE) {
        mwa_log_webauth_error(rc, status, mwa_func,
                              "webauth_token_encode_app", subject);
        return 0;
    }
    rc->at = app;
    fixup_setcookie(rc, app_cookie_name(), token);
    return 1;
}
