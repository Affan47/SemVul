krb5_ldap_delete_policy(krb5_context context, char *policyname)
{
    int                         refcount = 0;
    char                        *policy_dn = NULL;
    krb5_error_code             st = 0;
    LDAP                        *ld = NULL;
    kdb5_dal_handle             *dal_handle=NULL;
    krb5_ldap_context           *ldap_context=NULL;
    krb5_ldap_server_handle     *ldap_server_handle=NULL;

    if (policyname == NULL) {
        st = EINVAL;
        prepend_err_str(context, _("Ticket Policy Object DN missing"), st, st);
        goto cleanup;
    }


    SETUP_CONTEXT();
    GET_HANDLE();

    if ((st = krb5_ldap_name_to_policydn (context, policyname, &policy_dn)) != 0)
        goto cleanup;


    if ((st = krb5_ldap_get_reference_count (context, policy_dn,
                                             "krbTicketPolicyReference", &refcount, ld)) != 0)
        goto cleanup;

    if (refcount == 0) {
        if ((st=ldap_delete_ext_s(ld, policy_dn, NULL, NULL)) != 0) {
            prepend_err_str (context,ldap_err2string(st),st,st);

            goto cleanup;
        }
    } else {
        st = EINVAL;
        prepend_err_str(context,
                        _("Delete Failed: One or more Principals associated "
                          "with the Ticket Policy"), st, st);
        goto cleanup;
    }

cleanup:
    if (policy_dn != NULL)
        free (policy_dn);
    krb5_ldap_put_handle_to_pool(ldap_context, ldap_server_handle);
    return st;
}
