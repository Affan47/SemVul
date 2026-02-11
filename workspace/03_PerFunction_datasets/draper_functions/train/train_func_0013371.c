profile_host_realm(krb5_context context, krb5_hostrealm_moddata data,
                   const char *host, char ***realms_out)
{
    krb5_error_code ret;
    const char *p;
    char *prof_realm;

    *realms_out = NULL;


    if (k5_is_numeric_address(host))
        return KRB5_PLUGIN_NO_HANDLE;


    for (p = host; p != NULL; p = (*p == '.') ? p + 1 : strchr(p, '.')) {
        ret = profile_get_string(context->profile, KRB5_CONF_DOMAIN_REALM, p,
                                 NULL, NULL, &prof_realm);
        if (ret)
            return ret;
        if (prof_realm != NULL) {
            ret = k5_make_realmlist(prof_realm, realms_out);
            profile_release_string(prof_realm);
            return ret;
        }
    }
    return KRB5_PLUGIN_NO_HANDLE;
}
