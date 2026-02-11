posix_winsync_foreach_parent(Slapi_Entry *entry, char **attrs, plugin_search_entry_callback callback, void *callback_data)
{
    char *cookie = NULL;
    Slapi_Backend *be = NULL;

    char *value = slapi_entry_get_ndn(entry);
    size_t vallen = value ? strlen(value) : 0;
    char *filter_escaped_value = slapi_escape_filter_value(value, vallen);
    char *filter = slapi_ch_smprintf("(uniqueMember=%s)", filter_escaped_value);
    slapi_ch_free_string(&filter_escaped_value);

    Slapi_PBlock *search_pb = slapi_pblock_new();

    for (be = slapi_get_first_backend(&cookie); be;
         be = slapi_get_next_backend(cookie)) {
        const Slapi_DN *base_sdn = slapi_be_getsuffix(be, 0);
        if (base_sdn == NULL) {
            continue;
        }
        slapi_log_error(SLAPI_LOG_PLUGIN, POSIX_WINSYNC_PLUGIN_NAME,
                        "posix_winsync_foreach_parent: Searching subtree %s for %s\n",
                        slapi_sdn_get_dn(base_sdn),
                        filter);

        slapi_search_internal_set_pb(search_pb,
                                     slapi_sdn_get_dn(base_sdn),
                                     LDAP_SCOPE_SUBTREE,
                                     filter,
                                     attrs, 0, NULL, NULL,
                                     posix_winsync_get_plugin_identity(), 0);
        slapi_search_internal_callback_pb(search_pb, callback_data, 0, callback, 0);

        slapi_pblock_init(search_pb);
    }

    slapi_pblock_destroy(search_pb);
    slapi_ch_free((void**)&cookie);
    slapi_ch_free_string(&filter);
}
