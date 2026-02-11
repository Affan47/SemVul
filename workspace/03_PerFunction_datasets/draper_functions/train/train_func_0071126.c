krb5_tkt_creds_get_creds(krb5_context context, krb5_tkt_creds_context ctx,
                         krb5_creds *creds)
{
    if (ctx->state != STATE_COMPLETE)
        return KRB5_NO_TKT_SUPPLIED;
    return k5_copy_creds_contents(context, ctx->reply_creds, creds);
}
