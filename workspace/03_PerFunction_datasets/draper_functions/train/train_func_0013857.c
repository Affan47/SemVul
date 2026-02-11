read_instance_index_entries(ldbm_instance *inst)
{
    Slapi_PBlock *tmp_pb;
    int scope = LDAP_SCOPE_SUBTREE;
    const char *searchfilter = "(objectclass=nsIndex)";
    char *basedn = NULL;


    basedn = slapi_create_dn_string("cn=index,cn=%s,cn=%s,cn=plugins,cn=config",
                          inst->inst_name, inst->inst_li->li_plugin->plg_name);
    if (NULL == basedn) {
        LDAPDebug2Args(LDAP_DEBUG_ANY,
                       "read_instance_index_entries: "
                       "failed create index dn for plugin %s, instance %s\n",
                       inst->inst_li->li_plugin->plg_name, inst->inst_name);
        return 1;
    }


    slapi_config_register_callback(SLAPI_OPERATION_SEARCH, DSE_FLAG_PREOP,
        basedn, scope, searchfilter, ldbm_index_init_entry_callback,
        (void *) inst);


    tmp_pb = slapi_pblock_new();
    slapi_search_internal_set_pb(tmp_pb, basedn, LDAP_SCOPE_SUBTREE,
        searchfilter, NULL, 0, NULL, NULL, inst->inst_li->li_identity, 0);
    slapi_search_internal_pb (tmp_pb);


    slapi_config_remove_callback(SLAPI_OPERATION_SEARCH, DSE_FLAG_PREOP,
        basedn, scope, searchfilter, ldbm_index_init_entry_callback);
    slapi_free_search_results_internal(tmp_pb);
    slapi_pblock_destroy(tmp_pb);

    slapi_ch_free_string(&basedn);
    return 0;
}
