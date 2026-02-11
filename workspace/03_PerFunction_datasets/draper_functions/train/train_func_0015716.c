krb5_auth_con_setaddrs(krb5_context context, krb5_auth_context auth_context, krb5_address *local_addr, krb5_address *remote_addr)
{
    krb5_error_code     retval;


    if (auth_context->local_addr)
        (void) krb5_free_address(context, auth_context->local_addr);
    if (auth_context->remote_addr)
        (void) krb5_free_address(context, auth_context->remote_addr);

    retval = 0;
    if (local_addr)
        retval = krb5_copy_addr(context,
                                local_addr,
                                &auth_context->local_addr);
    else
        auth_context->local_addr = NULL;

    if (!retval && remote_addr)
        retval = krb5_copy_addr(context,
                                remote_addr,
                                &auth_context->remote_addr);
    else
        auth_context->remote_addr = NULL;

    return retval;
}
