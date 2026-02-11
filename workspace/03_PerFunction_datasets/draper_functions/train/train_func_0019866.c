dna_update_shared_config(struct configEntry * config_entry)
{
    int ret = LDAP_SUCCESS;

    if (config_entry && config_entry->shared_cfg_dn) {

        Slapi_PBlock *pb = NULL;
        LDAPMod mod_replace;
        LDAPMod *mods[2];
        char *replace_val[2];

        char remaining_vals[17];


        PR_snprintf(remaining_vals, sizeof(remaining_vals),"%" NSPRIu64,
                (long long unsigned int)config_entry->remaining);


        replace_val[0] = remaining_vals;
        replace_val[1] = 0;
        mod_replace.mod_op = LDAP_MOD_REPLACE;
        mod_replace.mod_type = DNA_REMAINING;
        mod_replace.mod_values = replace_val;
        mods[0] = &mod_replace;
        mods[1] = 0;

        pb = slapi_pblock_new();
        if (NULL == pb) {
            ret = LDAP_OPERATIONS_ERROR;
        } else {
            slapi_modify_internal_set_pb(pb, config_entry->shared_cfg_dn,
                                         mods, NULL, NULL, getPluginID(), 0);

            slapi_modify_internal_pb(pb);

            slapi_pblock_get(pb, SLAPI_PLUGIN_INTOP_RESULT, &ret);


            if (ret == LDAP_NO_SUCH_OBJECT) {
                Slapi_Entry *e = NULL;
                Slapi_DN *sdn =
                        slapi_sdn_new_normdn_byref(config_entry->shared_cfg_dn);


                e = slapi_entry_alloc();

                slapi_entry_init_ext(e, sdn, NULL);
                slapi_sdn_free(&sdn);

                slapi_entry_add_string(e, SLAPI_ATTR_OBJECTCLASS, DNA_SHAREDCONFIG);
                slapi_entry_add_string(e, DNA_HOSTNAME, hostname);
                slapi_entry_add_string(e, DNA_PORTNUM, portnum);
                if (secureportnum) {
                    slapi_entry_add_string(e, DNA_SECURE_PORTNUM, secureportnum);
                }
                slapi_entry_add_string(e, DNA_REMAINING, remaining_vals);


                slapi_pblock_init(pb);


                slapi_add_entry_internal_set_pb(pb, e, NULL, getPluginID(), 0);
                slapi_add_internal_pb(pb);
                slapi_pblock_get(pb, SLAPI_PLUGIN_INTOP_RESULT, &ret);
            }

            if (ret != LDAP_SUCCESS) {
                slapi_log_error(SLAPI_LOG_FATAL, DNA_PLUGIN_SUBSYSTEM,
                        "dna_update_shared_config: Unable to update shared config entry: %s [error %d]\n",
                        config_entry->shared_cfg_dn, ret);
            }

            slapi_pblock_destroy(pb);
            pb = NULL;
        }
    }

    return ret;
}
