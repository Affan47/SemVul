ids_sasl_getopt(
    void *context,
    const char *plugin_name,
    const char *option,
    const char **result,
    unsigned *len
)
{
    unsigned tmplen;

    LDAPDebug(LDAP_DEBUG_TRACE, "ids_sasl_getopt: plugin=%s option=%s\n",
              plugin_name ? plugin_name : "", option, 0);

    if (len == NULL) len = &tmplen;

    *result = NULL;
    *len = 0;

    if (strcasecmp(option, "enable") == 0) {
        *result = "USERDB/DIGEST-MD5,GSSAPI/GSSAPI";
    } else if (strcasecmp(option, "has_plain_passwords") == 0) {
        *result = "yes";
    } else if (strcasecmp(option, "LOG_LEVEL") == 0) {
        if (LDAPDebugLevelIsSet(LDAP_DEBUG_TRACE)) {
            *result = "6";
        }
    } else if (strcasecmp(option, "auxprop_plugin") == 0) {
        *result = "iDS";
    } else if (strcasecmp(option, "mech_list") == 0){
        *result = config_get_allowed_sasl_mechs();
    }

    if (*result) *len = strlen(*result);

    return SASL_OK;
}
