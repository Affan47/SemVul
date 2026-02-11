mep_load_config()
{
    int status = 0;
    int result;
    int i;
    Slapi_PBlock *search_pb;
    Slapi_Entry **entries = NULL;

    slapi_log_error(SLAPI_LOG_TRACE, MEP_PLUGIN_SUBSYSTEM,
                    "--> mep_load_config\n");


    mep_config_write_lock();
    mep_delete_config();

    search_pb = slapi_pblock_new();


    if (mep_get_config_area()) {

        slapi_log_error(SLAPI_LOG_PLUGIN, MEP_PLUGIN_SUBSYSTEM,
                        "mep_load_config: Looking for config entries "
                        "beneath \"%s\".\n", slapi_sdn_get_ndn(mep_get_config_area()));
        slapi_search_internal_set_pb(search_pb, slapi_sdn_get_ndn(mep_get_config_area()),
                                     LDAP_SCOPE_SUBTREE, "objectclass=*",
                                     NULL, 0, NULL, NULL, mep_get_plugin_id(), 0);
    } else {

        slapi_log_error(SLAPI_LOG_PLUGIN, MEP_PLUGIN_SUBSYSTEM,
                        "mep_load_config: Looking for config entries "
                        "beneath \"%s\".\n",
                         slapi_sdn_get_ndn(mep_get_plugin_sdn()));
        slapi_search_internal_set_pb(search_pb,
                                     slapi_sdn_get_ndn(mep_get_plugin_sdn()),
                                     LDAP_SCOPE_SUBTREE, "objectclass=*",
                                     NULL, 0, NULL, NULL, mep_get_plugin_id(), 0);
    }

    slapi_search_internal_pb(search_pb);
    slapi_pblock_get(search_pb, SLAPI_PLUGIN_INTOP_RESULT, &result);

    if (LDAP_SUCCESS != result) {
        if (mep_get_config_area() && (result == LDAP_NO_SUCH_OBJECT)) {
            slapi_log_error(SLAPI_LOG_PLUGIN, MEP_PLUGIN_SUBSYSTEM,
                            "mep_load_config: Config container \"%s\" does "
                            "not exist.\n", slapi_sdn_get_ndn(mep_get_config_area()));
            goto cleanup;
        } else {
            status = -1;
            goto cleanup;
        }
    }

    slapi_pblock_get(search_pb, SLAPI_PLUGIN_INTOP_SEARCH_ENTRIES,
                     &entries);


    for (i = 0; entries && (entries[i] != NULL); i++) {


        mep_parse_config_entry(entries[i], 1);
    }

  cleanup:
    slapi_free_search_results_internal(search_pb);
    slapi_pblock_destroy(search_pb);
    mep_config_unlock();
    slapi_log_error(SLAPI_LOG_TRACE, MEP_PLUGIN_SUBSYSTEM,
                    "<-- mep_load_config\n");

    return status;
}
