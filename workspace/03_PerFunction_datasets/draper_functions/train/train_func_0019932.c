try_fallback(krb5_context context, krb5_tkt_creds_context ctx)
{
    krb5_error_code code;
    char **hrealms;


    if (ctx->referral_count > 1)
        return ctx->reply_code;


    if (!krb5_is_referral_realm(&ctx->req_server->realm))
        return begin_non_referral(context, ctx);

    if (ctx->server->length < 2) {

        return KRB5_ERR_HOST_REALM_UNKNOWN;
    }


    code = krb5_get_fallback_host_realm(context, &ctx->server->data[1],
                                        &hrealms);
    if (code != 0)
        return code;


    if (data_eq_string(ctx->server->realm, hrealms[0])) {
        krb5_free_host_realm(context, hrealms);
        return begin_non_referral(context, ctx);
    }


    krb5_free_data_contents(context, &ctx->server->realm);
    ctx->server->realm = string2data(hrealms[0]);
    free(hrealms);
    TRACE_TKT_CREDS_FALLBACK(context, &ctx->server->realm);


    ctx->getting_tgt_for = STATE_NON_REFERRAL;
    return begin_get_tgt(context, ctx);
}
