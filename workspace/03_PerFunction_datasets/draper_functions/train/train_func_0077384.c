dna_activate_next_range(struct configEntry *config_entry)
{
    Slapi_PBlock *pb = NULL;
    LDAPMod mod_maxval;
    LDAPMod mod_nextval;
    LDAPMod mod_nextrange;
    LDAPMod *mods[4];
    char *maxval_vals[2];
    char *nextval_vals[2];
    char *nextrange_vals[1];

    char maxval_val[17];
    char nextval_val[17];
    int ret = 0;


    PR_snprintf(maxval_val, sizeof(maxval_val),"%" NSPRIu64, (long long unsigned int)config_entry->next_range_upper);
    PR_snprintf(nextval_val, sizeof(nextval_val),"%" NSPRIu64, (long long unsigned int)config_entry->next_range_lower);

    maxval_vals[0] = maxval_val;
    maxval_vals[1] = 0;
    nextval_vals[0] = nextval_val;
    nextval_vals[1] = 0;
    nextrange_vals[0] = 0;

    mod_maxval.mod_op = LDAP_MOD_REPLACE;
    mod_maxval.mod_type = DNA_MAXVAL;
    mod_maxval.mod_values = maxval_vals;
    mod_nextval.mod_op = LDAP_MOD_REPLACE;
    mod_nextval.mod_type = DNA_NEXTVAL;
    mod_nextval.mod_values = nextval_vals;
    mod_nextrange.mod_op = LDAP_MOD_DELETE;
    mod_nextrange.mod_type = DNA_NEXT_RANGE;
    mod_nextrange.mod_values = nextrange_vals;

    mods[0] = &mod_maxval;
    mods[1] = &mod_nextval;
    mods[2] = &mod_nextrange;
    mods[3] = 0;


    pb = slapi_pblock_new();
    if (NULL == pb) {
        ret = LDAP_OPERATIONS_ERROR;
        goto bail;
    }

    slapi_modify_internal_set_pb(pb, config_entry->dn,
                                 mods, 0, 0, getPluginID(), 0);

    slapi_modify_internal_pb(pb);

    slapi_pblock_get(pb, SLAPI_PLUGIN_INTOP_RESULT, &ret);

    slapi_pblock_destroy(pb);
    pb = NULL;

    if (ret != LDAP_SUCCESS) {
        slapi_log_error(SLAPI_LOG_FATAL, DNA_PLUGIN_SUBSYSTEM,
                        "dna_activate_next_range: Error updating "
                        "configuration entry [err=%d]\n", ret);
    } else {

        config_entry->maxval = config_entry->next_range_upper;
        config_entry->nextval = config_entry->next_range_lower;
        config_entry->next_range_upper = 0;
        config_entry->next_range_lower = 0;
        config_entry->remaining = ((config_entry->maxval - config_entry->nextval + 1) /
                                    config_entry->interval);

        dna_update_shared_config(config_entry);
    }

bail:
    return ret;
}
