ldbm_config_add_dse_entries(struct ldbminfo *li, char **entries, char *string1, char *string2, char *string3, int flags)
{
    int x;
    Slapi_Entry *e;
    Slapi_PBlock *util_pb = NULL;
    int rc;
    int result;
    char entry_string[512];
    int dont_write_file = 0;
    char ebuf[BUFSIZ];

    if (flags & LDBM_INSTANCE_CONFIG_DONT_WRITE) {
        dont_write_file = 1;
    }

    for(x = 0; strlen(entries[x]) > 0; x++) {
        util_pb = slapi_pblock_new();
        PR_snprintf(entry_string, 512, entries[x], string1, string2, string3);
        e = slapi_str2entry(entry_string, 0);
        PL_strncpyz(ebuf, slapi_entry_get_dn_const(e), sizeof(ebuf));
        slapi_add_entry_internal_set_pb(util_pb, e, NULL, li->li_identity, 0);
        slapi_pblock_set(util_pb, SLAPI_DSE_DONT_WRITE_WHEN_ADDING,
                         &dont_write_file);
        rc = slapi_add_internal_pb(util_pb);
        slapi_pblock_get(util_pb, SLAPI_PLUGIN_INTOP_RESULT, &result);
        if (!rc && (result == LDAP_SUCCESS)) {
            LDAPDebug(LDAP_DEBUG_CONFIG, "Added database config entry [%s]\n",
                      ebuf, 0, 0);
        } else if (result == LDAP_ALREADY_EXISTS) {
            LDAPDebug(LDAP_DEBUG_TRACE, "Database config entry [%s] already exists - skipping\n",
                      ebuf, 0, 0);
        } else {
            LDAPDebug(LDAP_DEBUG_ANY, "Unable to add config entry [%s] to the DSE: %d %d\n",
                      ebuf, result, rc);
        }
        slapi_pblock_destroy(util_pb);
    }

    return 0;
}
