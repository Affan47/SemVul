krb5_init_creds_get_times(krb5_context context,
                          krb5_init_creds_context ctx,
                          krb5_ticket_times *times)
{
    if (!ctx->complete)
        return KRB5_NO_TKT_SUPPLIED;

    *times = ctx->cred.times;

    return 0;
}
