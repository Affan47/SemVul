krb5_ldap_free_server_context_params(krb5_ldap_context *ldap_context)
{
    int                         i=0;
    krb5_ldap_server_handle     *ldap_server_handle=NULL, *next_ldap_server_handle=NULL;

    if (ldap_context == NULL)
        return 0;


    if (ldap_context->server_info_list) {
        while (ldap_context->server_info_list[i]) {
            if (ldap_context->server_info_list[i]->server_name) {
                free (ldap_context->server_info_list[i]->server_name);
            }
            if (ldap_context->server_info_list[i]->ldap_server_handles) {
                ldap_server_handle = ldap_context->server_info_list[i]->ldap_server_handles;
                while (ldap_server_handle) {
                    ldap_unbind_ext_s(ldap_server_handle->ldap_handle, NULL, NULL);
                    ldap_server_handle->ldap_handle = NULL;
                    next_ldap_server_handle = ldap_server_handle->next;
                    free(ldap_server_handle);
                    ldap_server_handle = next_ldap_server_handle;
                }
            }
            free(ldap_context->server_info_list[i]);
            i++;
        }
        free(ldap_context->server_info_list);
    }

    if (ldap_context->conf_section != NULL) {
        free(ldap_context->conf_section);
        ldap_context->conf_section = NULL;
    }

    if (ldap_context->bind_dn != NULL) {
        free(ldap_context->bind_dn);
        ldap_context->bind_dn = NULL;
    }

    if (ldap_context->bind_pwd != NULL) {
        memset(ldap_context->bind_pwd, 0, strlen(ldap_context->bind_pwd));
        free(ldap_context->bind_pwd);
        ldap_context->bind_pwd = NULL;
    }

    if (ldap_context->service_password_file != NULL) {
        free(ldap_context->service_password_file);
        ldap_context->service_password_file = NULL;
    }

    if (ldap_context->certificates) {
        i=0;
        while (ldap_context->certificates[i] != NULL) {
            free(ldap_context->certificates[i]->certificate);
            free(ldap_context->certificates[i]);
            ++i;
        }
        free(ldap_context->certificates);
    }

    return(0);
}
