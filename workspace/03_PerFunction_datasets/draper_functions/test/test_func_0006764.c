handle_error_token(const struct webauth_token_error *err, MWA_REQ_CTXT *rc)
{
    static const char *mwa_func = "handle_error_token";
    const char *log_message;
    unsigned long now;

    now = time(NULL);
    if (err->creation + rc->sconf->token_max_ttl < now) {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, rc->r->server,
                     "mod_webauth: %s: error token too old", mwa_func);
        return failure_redirect(rc);
    }
    if (rc->sconf->debug)
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, rc->r->server,
                     "mod_webauth: %s: parsed an error token(%lu, %s)",
                     mwa_func, err->code, err->message);

    switch (err->code) {
    case WA_PEC_LOGIN_CANCELED:

        return login_canceled_redirect(rc);
        break;
    default:


        log_message = "unhandled error";
        break;
    }
    ap_log_error(APLOG_MARK, APLOG_ALERT, 0, rc->r->server,
                 "mod_webauth: %s: %s: %s (%lu)", mwa_func, log_message,
                 err->message, err->code);
    return failure_redirect(rc);
}
