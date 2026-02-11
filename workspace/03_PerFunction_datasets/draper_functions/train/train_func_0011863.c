create_service_token_from_req(MWK_REQ_CTXT *rc,
                              MWK_REQUESTER_CREDENTIAL *req_cred,
                              MWK_RETURNED_TOKEN *rtoken)
{
    static const char *mwk_func = "create_service_token_from_req";
    int status;
    size_t len;
    enum mwk_status ms;
    time_t expiration;
    struct webauth_token token;
    struct webauth_key *key;


    if (strcmp(req_cred->type, "krb5") != 0) {
        return set_errorResponse(rc, WA_PEC_INVALID_REQUEST,
                                 "can only create service-tokens with "
                                 "<requesterCredential> of type krb",
                                 mwk_func, true);
    }

    if (!mwk_has_service_access(rc, req_cred->subject)) {
        return set_errorResponse(rc, WA_PEC_UNAUTHORIZED,
                                 "not authorized to get a service token",
                                 mwk_func, true);
    }

    status = webauth_key_create(rc->ctx, WA_KEY_AES, WA_AES_128, NULL, &key);
    if (status != WA_ERR_NONE) {
        mwk_log_webauth_error(rc->ctx, rc->r->server, status, mwk_func,
                              "webauth_create_key", NULL);
        return set_errorResponse(rc, WA_PEC_SERVER_FAILURE,
                                 "can't generate session key", mwk_func,
                                 false);
    }

    memset(&token, 0, sizeof(token));
    expiration = time(NULL) + rc->sconf->service_lifetime;
    token.type = WA_TOKEN_WEBKDC_SERVICE;
    token.token.webkdc_service.subject = req_cred->subject;
    token.token.webkdc_service.session_key = key->data;
    token.token.webkdc_service.session_key_len = key->length;
    token.token.webkdc_service.expiration = expiration;
    ms = make_token(rc, &token, &rtoken->token_data, mwk_func);

    if (!ms)
        return MWK_ERROR;

    rtoken->expires = apr_psprintf(rc->r->pool, "%lu",
                                   (unsigned long) expiration);

    len = key->length;
    rtoken->session_key = apr_palloc(rc->r->pool, apr_base64_encode_len(len));
    apr_base64_encode(rtoken->session_key, (char *) key->data, len);

    rtoken->subject = req_cred->subject;
    rtoken->info = " type=service";

    return MWK_OK;
}
