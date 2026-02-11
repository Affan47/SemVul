mep_add_managed_entry(struct configEntry *config,
    Slapi_Entry *origin)
{
    Slapi_Entry *managed_entry = NULL;
    char *managed_dn = NULL;
    Slapi_PBlock *mod_pb = slapi_pblock_new();
    int result = LDAP_SUCCESS;


    slapi_log_error(SLAPI_LOG_PLUGIN, MEP_PLUGIN_SUBSYSTEM,
                    "mep_add_managed_entry: Creating a managed "
                    "entry from origin entry \"%s\" using "
                    "config \"%s\".\n", slapi_entry_get_dn(origin),
                    slapi_sdn_get_dn(config->sdn));
    managed_entry = mep_create_managed_entry(config, origin);
    if (managed_entry == NULL) {
        slapi_log_error(SLAPI_LOG_FATAL, MEP_PLUGIN_SUBSYSTEM,
                    "mep_add_managed_entry: Unable to create a managed "
                    "entry from origin entry \"%s\" using config "
                    "\"%s\".\n", slapi_entry_get_dn(origin), slapi_sdn_get_dn(config->sdn));
    } else {


        managed_dn = slapi_ch_strdup(slapi_entry_get_dn(managed_entry));


        slapi_log_error(SLAPI_LOG_PLUGIN, MEP_PLUGIN_SUBSYSTEM,
                    "Adding managed entry \"%s\" for origin "
                    "entry \"%s\"\n.", managed_dn, slapi_entry_get_dn(origin));
        slapi_add_entry_internal_set_pb(mod_pb, managed_entry, NULL,
                                        mep_get_plugin_id(), 0);
        slapi_add_internal_pb(mod_pb);
        slapi_pblock_get(mod_pb, SLAPI_PLUGIN_INTOP_RESULT, &result);

        if (result != LDAP_SUCCESS) {
            slapi_log_error(SLAPI_LOG_FATAL, MEP_PLUGIN_SUBSYSTEM,
                        "mep_add_managed_entry: Unable to add managed "
                        "entry \"%s\" for origin entry \"%s\" (%s).\n",
                        managed_dn, slapi_entry_get_dn(origin),
                        ldap_err2string(result));
        } else {

            LDAPMod oc_mod;
            LDAPMod pointer_mod;
            LDAPMod *mods[3];
            char *oc_vals[2];
            char *pointer_vals[2];


            slapi_pblock_init(mod_pb);


            oc_vals[0] = MEP_ORIGIN_OC;
            oc_vals[1] = 0;
            oc_mod.mod_op = LDAP_MOD_ADD;
            oc_mod.mod_type = SLAPI_ATTR_OBJECTCLASS;
            oc_mod.mod_values = oc_vals;


            pointer_vals[0] = managed_dn;
            pointer_vals[1] = 0;
            pointer_mod.mod_op = LDAP_MOD_ADD;
            pointer_mod.mod_type = MEP_MANAGED_ENTRY_TYPE;
            pointer_mod.mod_values = pointer_vals;

            mods[0] = &oc_mod;
            mods[1] = &pointer_mod;
            mods[2] = 0;


            slapi_log_error(SLAPI_LOG_PLUGIN, MEP_PLUGIN_SUBSYSTEM,
                    "Adding %s pointer to \"%s\" in entry \"%s\"\n.",
                    MEP_MANAGED_ENTRY_TYPE, managed_dn, slapi_entry_get_dn(origin));
            slapi_modify_internal_set_pb_ext(mod_pb,
                                            slapi_entry_get_sdn(origin),
                                            mods, 0, 0, mep_get_plugin_id(), 0);
            slapi_modify_internal_pb(mod_pb);
            slapi_pblock_get(mod_pb, SLAPI_PLUGIN_INTOP_RESULT, &result);

            if (result != LDAP_SUCCESS) {
                slapi_log_error(SLAPI_LOG_FATAL, MEP_PLUGIN_SUBSYSTEM,
                            "mep_add_managed_entry: Unable to add pointer to "
                            "managed entry \"%s\" in origin entry \"%s\" "
                            "(%s).\n", managed_dn, slapi_entry_get_dn(origin),
                            ldap_err2string(result));
            }
        }
    }

    slapi_ch_free_string(&managed_dn);
    slapi_pblock_destroy(mod_pb);
}
