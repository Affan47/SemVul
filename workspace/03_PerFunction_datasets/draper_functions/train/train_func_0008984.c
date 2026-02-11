krb5_tkt_creds_get_times(krb5_context context, krb5_tkt_creds_context ctx,
                         krb5_ticket_times *times)
{
    if (ctx->state != STATE_COMPLETE)
        return KRB5_NO_TKT_SUPPLIED;
    *times = ctx->reply_creds->times;
    return 0;
}
