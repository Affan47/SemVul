mep_init(Slapi_PBlock *pb)
{
    int status = 0;
    char *plugin_identity = NULL;
    Slapi_Entry *plugin_entry = NULL;
    char *plugin_type = NULL;
    int preadd = SLAPI_PLUGIN_PRE_ADD_FN;
    int premod = SLAPI_PLUGIN_PRE_MODIFY_FN;
    int predel = SLAPI_PLUGIN_PRE_DELETE_FN;
    int premdn = SLAPI_PLUGIN_PRE_MODRDN_FN;

    slapi_log_error(SLAPI_LOG_TRACE, MEP_PLUGIN_SUBSYSTEM,
                    "--> mep_init\n");

    if ((slapi_pblock_get(pb, SLAPI_PLUGIN_CONFIG_ENTRY, &plugin_entry) == 0) &&
        plugin_entry &&
        (plugin_type = slapi_entry_attr_get_charptr(plugin_entry, "nsslapd-plugintype")) &&
        plugin_type && strstr(plugin_type, "betxn")) {
        plugin_is_betxn = 1;
        preadd = SLAPI_PLUGIN_BE_TXN_PRE_ADD_FN;
        premod = SLAPI_PLUGIN_BE_TXN_PRE_MODIFY_FN;
        predel = SLAPI_PLUGIN_BE_TXN_PRE_DELETE_FN;
        premdn = SLAPI_PLUGIN_BE_TXN_PRE_MODRDN_FN;
    }
    slapi_ch_free_string(&plugin_type);


    slapi_pblock_get(pb, SLAPI_PLUGIN_IDENTITY, &plugin_identity);
    PR_ASSERT(plugin_identity);
    mep_set_plugin_id(plugin_identity);


    if (slapi_pblock_set(pb, SLAPI_PLUGIN_VERSION,
                         SLAPI_PLUGIN_VERSION_01) != 0 ||
        slapi_pblock_set(pb, SLAPI_PLUGIN_START_FN,
                         (void *) mep_start) != 0 ||
        slapi_pblock_set(pb, SLAPI_PLUGIN_CLOSE_FN,
                         (void *) mep_close) != 0 ||
        slapi_pblock_set(pb, SLAPI_PLUGIN_DESCRIPTION,
                         (void *) &pdesc) != 0 ||
        slapi_pblock_set(pb, premod, (void *) mep_mod_pre_op) != 0 ||
        slapi_pblock_set(pb, preadd, (void *) mep_add_pre_op) != 0 ||
        slapi_pblock_set(pb, predel, (void *) mep_del_pre_op) != 0 ||
        slapi_pblock_set(pb, premdn, (void *) mep_modrdn_pre_op) != 0) {
        slapi_log_error(SLAPI_LOG_FATAL, MEP_PLUGIN_SUBSYSTEM,
                        "mep_init: failed to register plugin\n");
        status = -1;
    }

    if (!status && !plugin_is_betxn &&
        slapi_register_plugin("internalpostoperation",
                              1,
                              "mep_init",
                              mep_internal_postop_init,
                              MEP_INT_POSTOP_DESC,
                              NULL,
                              plugin_identity
        )) {
        slapi_log_error(SLAPI_LOG_FATAL, MEP_PLUGIN_SUBSYSTEM,
                        "mep_init: failed to register internalpostoperation plugin\n");
        status = -1;
    }

    if (!status) {
        plugin_type = plugin_is_betxn ? "betxnpostoperation" : "postoperation";
        if (slapi_register_plugin(plugin_type,
                                  1,
                                  "mep_init",
                                  mep_postop_init,
                                  MEP_POSTOP_DESC,
                                  NULL,
                                  plugin_identity
        )) {
            slapi_log_error(SLAPI_LOG_FATAL, MEP_PLUGIN_SUBSYSTEM,
                            "mep_init: failed to register plugin\n");
            status = -1;
        }
    }

    slapi_log_error(SLAPI_LOG_TRACE, MEP_PLUGIN_SUBSYSTEM,
                    "<-- mep_init\n");
    return status;
}
