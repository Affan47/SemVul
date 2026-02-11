print_policy_params(krb5_ldap_policy_params *policyparams, int mask)
{

    printf("%25s: %s\n", "Ticket policy", policyparams->policy);


    if (mask & LDAP_POLICY_MAXTKTLIFE)
        printf("%25s: %s\n", "Maximum ticket life", strdur(policyparams->maxtktlife));
    if (mask & LDAP_POLICY_MAXRENEWLIFE)
        printf("%25s: %s\n", "Maximum renewable life", strdur(policyparams->maxrenewlife));


    printf("%25s: ", "Ticket flags");
    if (mask & LDAP_POLICY_TKTFLAGS) {
        int ticketflags = policyparams->tktflags;

        if (ticketflags & KRB5_KDB_DISALLOW_POSTDATED)
            printf("%s ","DISALLOW_POSTDATED");

        if (ticketflags & KRB5_KDB_DISALLOW_FORWARDABLE)
            printf("%s ","DISALLOW_FORWARDABLE");

        if (ticketflags & KRB5_KDB_DISALLOW_RENEWABLE)
            printf("%s ","DISALLOW_RENEWABLE");

        if (ticketflags & KRB5_KDB_DISALLOW_PROXIABLE)
            printf("%s ","DISALLOW_PROXIABLE");

        if (ticketflags & KRB5_KDB_DISALLOW_DUP_SKEY)
            printf("%s ","DISALLOW_DUP_SKEY");

        if (ticketflags & KRB5_KDB_REQUIRES_PRE_AUTH)
            printf("%s ","REQUIRES_PRE_AUTH");

        if (ticketflags & KRB5_KDB_REQUIRES_HW_AUTH)
            printf("%s ","REQUIRES_HW_AUTH");

        if (ticketflags & KRB5_KDB_DISALLOW_SVR)
            printf("%s ","DISALLOW_SVR");

        if (ticketflags & KRB5_KDB_DISALLOW_TGT_BASED)
            printf("%s ","DISALLOW_TGT_BASED");

        if (ticketflags & KRB5_KDB_DISALLOW_ALL_TIX)
            printf("%s ","DISALLOW_ALL_TIX");

        if (ticketflags & KRB5_KDB_REQUIRES_PWCHANGE)
            printf("%s ","REQUIRES_PWCHANGE");

        if (ticketflags & KRB5_KDB_PWCHANGE_SERVICE)
            printf("%s ","PWCHANGE_SERVICE");
    }
    printf("\n");

    return;
}
