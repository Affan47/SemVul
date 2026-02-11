renew(krb5_context ctx, struct config *config, krb5_error_code status)
{
    krb5_ccache ccache = NULL;
    krb5_error_code code;
    krb5_principal user = NULL;
    krb5_creds creds;
    bool creds_valid = false;


    if (status != 0 && status != KRB5KRB_AP_ERR_TKT_EXPIRED) {
        if (status == KRB5KDC_ERR_KEY_EXP)
            warn("ticket cannot be renewed for long enough");
        else
            warn_krb5(ctx, status, "error reading ticket cache");
        if (!config->ignore_errors)
            exit_cleanup(ctx, config, 1);
        return status;
    }
    memset(&creds, 0, sizeof(creds));
    code = krb5_cc_resolve(ctx, config->cache, &ccache);
    if (code != 0) {
        warn_krb5(ctx, code, "error opening ticket cache");
        if (!config->ignore_errors)
            exit_cleanup(ctx, config, 1);
        return code;
    }
    code = krb5_cc_get_principal(ctx, ccache, &user);
    if (code != 0) {
        warn_krb5(ctx, code, "error reading ticket cache");
        krb5_cc_close(ctx, ccache);
        if (!config->ignore_errors)
            exit_cleanup(ctx, config, 1);
        return code;
    }
    if (config->verbose) {
        char *name;

        code = krb5_unparse_name(ctx, user, &name);
        if (code != 0)
            warn_krb5(ctx, code, "error unparsing name");
        else {
            notice("renewing credentials for %s", name);
            krb5_free_unparsed_name(ctx, name);
        }
    }


    code = krb5_get_renewed_creds(ctx, &creds, user, ccache, NULL);
    creds_valid = true;
    if (code != 0) {
        warn_krb5(ctx, code, "error renewing credentials");
        goto done;
    }


    code = krb5_cc_initialize(ctx, ccache, user);
    if (code != 0) {
        warn_krb5(ctx, code, "error reinitializing cache");
        goto done;
    }
    code = krb5_cc_store_cred(ctx, ccache, &creds);
    if (code != 0) {
        warn_krb5(ctx, code, "error storing credentials");
        goto done;
    }

done:
    if (ccache != NULL)
        krb5_cc_close(ctx, ccache);
    if (user != NULL)
        krb5_free_principal(ctx, user);
    if (creds_valid)
        krb5_free_cred_contents(ctx, &creds);
    return code;
}
