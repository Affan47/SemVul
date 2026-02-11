step_get_tgt_offpath(krb5_context context, krb5_tkt_creds_context ctx)
{
    krb5_error_code code;
    const krb5_data *tgt_realm;


    if (ctx->reply_code != 0)
        return ctx->reply_code;


    if (!IS_TGS_PRINC(ctx->reply_creds->server))
        return KRB5_KDCREP_MODIFIED;


    krb5_free_creds(context, ctx->cur_tgt);
    ctx->cur_tgt = ctx->reply_creds;
    ctx->reply_creds = NULL;


    tgt_realm = &ctx->cur_tgt->server->data[1];
    if (seen_realm_before(context, ctx, tgt_realm))
        return KRB5_KDC_UNREACH;
    code = remember_realm(context, ctx, tgt_realm);
    if (code != 0)
        return code;

    if (data_eq(*tgt_realm, ctx->server->realm)) {

        TRACE_TKT_CREDS_TARGET_TGT_OFFPATH(context, ctx->cur_tgt->server);
        return end_get_tgt(context, ctx);
    } else if (ctx->offpath_count++ >= KRB5_REFERRAL_MAXHOPS) {

        return KRB5_KDCREP_MODIFIED;
    }

    return make_request_for_tgt(context, ctx, &ctx->server->realm);
}
