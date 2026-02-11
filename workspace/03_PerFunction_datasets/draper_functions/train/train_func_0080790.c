get_tgt_request(krb5_context context, krb5_tkt_creds_context ctx)
{
    krb5_error_code code;
    krb5_creds *cached_tgt;

    while (1) {

        code = get_cached_tgt(context, ctx, ctx->next_realm, &cached_tgt);
        if (code != 0)
            return code;
        if (cached_tgt != NULL) {

            TRACE_TKT_CREDS_CACHED_INTERMEDIATE_TGT(context, cached_tgt);
            krb5_free_creds(context, ctx->cur_tgt);
            ctx->cur_tgt = cached_tgt;
            if (ctx->next_realm == ctx->last_realm)
                return end_get_tgt(context, ctx);
            ctx->cur_realm = ctx->next_realm;
            ctx->next_realm = ctx->last_realm;
            continue;
        }

        return make_request_for_tgt(context, ctx, ctx->next_realm);
    }
}
