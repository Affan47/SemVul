krb5_ldap_create_policy(krb5_context context, krb5_ldap_policy_params *policy,
                        int mask)
{
    krb5_error_code             st=0;
    LDAP                        *ld=NULL;
    char                        *strval[3]={NULL}, *policy_dn = NULL;
    LDAPMod                     **mods=NULL;
    kdb5_dal_handle             *dal_handle=NULL;
    krb5_ldap_context           *ldap_context=NULL;
    krb5_ldap_server_handle     *ldap_server_handle=NULL;


    if (policy == NULL || policy->policy == NULL) {
        st = EINVAL;
        krb5_set_error_message(context, st, _("Ticket Policy Name missing"));
        goto cleanup;
    }

    SETUP_CONTEXT();
    GET_HANDLE();

    if ((st = krb5_ldap_name_to_policydn (context, policy->policy, &policy_dn)) != 0)
        goto cleanup;

    memset(strval, 0, sizeof(strval));
    strval[0] = policy->policy;
    if ((st=krb5_add_str_mem_ldap_mod(&mods, "cn", LDAP_MOD_ADD, strval)) != 0)
        goto cleanup;

    memset(strval, 0, sizeof(strval));
    strval[0] = "krbTicketPolicy";
    strval[1] = "krbTicketPolicyaux";
    if ((st=krb5_add_str_mem_ldap_mod(&mods, "objectclass", LDAP_MOD_ADD, strval)) != 0)
        goto cleanup;

    if (mask & LDAP_POLICY_MAXTKTLIFE) {
        if ((st=krb5_add_int_mem_ldap_mod(&mods, "krbmaxticketlife", LDAP_MOD_ADD,
                                          policy->maxtktlife)) != 0)
            goto cleanup;
    }

    if (mask & LDAP_POLICY_MAXRENEWLIFE) {
        if ((st=krb5_add_int_mem_ldap_mod(&mods, "krbmaxrenewableage", LDAP_MOD_ADD,
                                          policy->maxrenewlife)) != 0)
            goto cleanup;
    }

    if (mask & LDAP_POLICY_TKTFLAGS) {
        if ((st=krb5_add_int_mem_ldap_mod(&mods, "krbticketflags", LDAP_MOD_ADD,
                                          policy->tktflags)) != 0)
            goto cleanup;
    }


    if ((st=ldap_add_ext_s(ld, policy_dn, mods, NULL, NULL)) != LDAP_SUCCESS) {
        st = set_ldap_error (context, st, OP_ADD);
        goto cleanup;
    }

cleanup:
    if (policy_dn != NULL)
        free(policy_dn);

    ldap_mods_free(mods, 1);
    krb5_ldap_put_handle_to_pool(ldap_context, ldap_server_handle);
    return st;
}
