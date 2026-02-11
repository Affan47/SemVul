krb5_ldap_free_realm_params(krb5_ldap_realm_params *rparams)
{
    int i=0;

    if (rparams) {
        if (rparams->realmdn)
            free(rparams->realmdn);

        if (rparams->realm_name)
            free(rparams->realm_name);

        if (rparams->subtree) {
            for (i=0; i<rparams->subtreecount && rparams->subtree[i] ; i++)
                free(rparams->subtree[i]);
            free(rparams->subtree);
        }

        if (rparams->kdcservers) {
            for (i=0; rparams->kdcservers[i]; ++i)
                free(rparams->kdcservers[i]);
            free(rparams->kdcservers);
        }

        if (rparams->adminservers) {
            for (i=0; rparams->adminservers[i]; ++i)
                free(rparams->adminservers[i]);
            free(rparams->adminservers);
        }

        if (rparams->passwdservers) {
            for (i=0; rparams->passwdservers[i]; ++i)
                free(rparams->passwdservers[i]);
            free(rparams->passwdservers);
        }

        if (rparams->tl_data) {
            if (rparams->tl_data->tl_data_contents)
                free(rparams->tl_data->tl_data_contents);
            free(rparams->tl_data);
        }

        free(rparams);
    }
    return;
}
