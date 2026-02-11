krb5_put_ldap_handle(krb5_ldap_server_handle *ldap_server_handle)
{

    if (ldap_server_handle == NULL)
        return 0;

    ldap_server_handle->next = ldap_server_handle->server_info->ldap_server_handles;
    ldap_server_handle->server_info->ldap_server_handles = ldap_server_handle;
    return 0;
}
