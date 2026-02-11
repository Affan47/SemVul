krb5_ldap_free_server_params(krb5_ldap_context *ldap_context)
{
    if (ldap_context == NULL)
        return 0;

    krb5_ldap_free_server_context_params(ldap_context);

    k5_mutex_destroy(&ldap_context->hndl_lock);
    free(ldap_context);
    return(0);
}
