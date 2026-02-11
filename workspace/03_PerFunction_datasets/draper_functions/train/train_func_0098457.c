usn_bepostop_init(Slapi_PBlock *pb)
{
    int rc = SLAPI_PLUGIN_SUCCESS;
    Slapi_Entry *plugin_entry = NULL;
    char *plugin_type = NULL;
    int postadd = SLAPI_PLUGIN_BE_POST_ADD_FN;
    int postmod = SLAPI_PLUGIN_BE_POST_MODIFY_FN;
    int postmdn = SLAPI_PLUGIN_BE_POST_MODRDN_FN;
    int postdel = SLAPI_PLUGIN_BE_POST_DELETE_FN;

    if ((slapi_pblock_get(pb, SLAPI_PLUGIN_CONFIG_ENTRY, &plugin_entry) == 0) &&
        plugin_entry &&
        (plugin_type = slapi_entry_attr_get_charptr(plugin_entry,
                                                    "nsslapd-plugintype")) &&
        plugin_type && strstr(plugin_type, "betxn")) {
        postadd = SLAPI_PLUGIN_BE_TXN_POST_ADD_FN;
        postmod = SLAPI_PLUGIN_BE_TXN_POST_MODIFY_FN;
        postmdn = SLAPI_PLUGIN_BE_TXN_POST_MODRDN_FN;
        postdel = SLAPI_PLUGIN_BE_TXN_POST_DELETE_FN;
    }
    slapi_ch_free_string(&plugin_type);

    if ((slapi_pblock_set(pb, postadd, (void *)usn_bepostop) != 0) ||
        (slapi_pblock_set(pb, postdel, (void *)usn_bepostop_delete) != 0) ||
        (slapi_pblock_set(pb, postmod, (void *)usn_bepostop_modify) != 0) ||
        (slapi_pblock_set(pb, postmdn, (void *)usn_bepostop) != 0)) {
        slapi_log_error(SLAPI_LOG_FATAL, USN_PLUGIN_SUBSYSTEM,
                     "usn_bepostop_init: failed to register bepostop plugin\n");
        rc = SLAPI_PLUGIN_FAILURE;
    }

    return rc;
}
