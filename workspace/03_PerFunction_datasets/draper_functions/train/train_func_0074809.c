begin_get_tgt(krb5_context context, krb5_tkt_creds_context ctx)
{
    krb5_error_code code;
    krb5_creds *cached_tgt;
    krb5_boolean is_local_service;

    ctx->state = STATE_GET_TGT;

    is_local_service = data_eq(ctx->client->realm, ctx->server->realm);
    if (!is_local_service) {

        code = get_cached_tgt(context, ctx, &ctx->server->realm, &cached_tgt);
        if (code != 0)
            return code;
        if (cached_tgt != NULL) {
            TRACE_TKT_CREDS_CACHED_SERVICE_TGT(context, cached_tgt);
            krb5_free_creds(context, ctx->cur_tgt);
            ctx->cur_tgt = cached_tgt;
            return end_get_tgt(context, ctx);
        }
    }


    krb5_free_creds(context, ctx->cur_tgt);
    ctx->cur_tgt = NULL;
    code = get_cached_local_tgt(context, ctx, &ctx->cur_tgt);
    if (code != 0)
        return code;
    TRACE_TKT_CREDS_LOCAL_TGT(context, ctx->cur_tgt);

    if (is_local_service)
        return end_get_tgt(context, ctx);


    code = init_realm_path(context, ctx);
    if (code != 0)
        return code;


    krb5int_free_data_list(context, ctx->realms_seen);
    ctx->realms_seen = NULL;


    return get_tgt_request(context, ctx);
}
