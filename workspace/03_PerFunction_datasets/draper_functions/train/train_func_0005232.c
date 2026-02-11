get_creds_from_tgs_reply(krb5_context context, krb5_tkt_creds_context ctx,
                         krb5_data *reply)
{
    krb5_error_code code;

    krb5_free_creds(context, ctx->reply_creds);
    ctx->reply_creds = NULL;
    code = krb5int_process_tgs_reply(context, ctx->fast_state,
                                     reply, ctx->cur_tgt, ctx->kdcopt,
                                     ctx->cur_tgt->addresses, NULL,
                                     ctx->tgs_in_creds, ctx->timestamp,
                                     ctx->nonce, ctx->subkey, NULL, NULL,
                                     &ctx->reply_creds);
    if (code == KRB5KRB_ERR_RESPONSE_TOO_BIG) {

        code = set_caller_request(context, ctx);
        if (code != 0)
            return code;
        return KRB5KRB_ERR_RESPONSE_TOO_BIG;
    }


    TRACE_TKT_CREDS_RESPONSE_CODE(context, code);
    ctx->reply_code = code;
    return 0;
}
