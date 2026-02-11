initialize_stats_table(void)
{
    netsnmp_table_registration_info *ops_table_info = NULL;
    netsnmp_table_registration_info *entries_table_info = NULL;
    netsnmp_table_registration_info *entity_table_info = NULL;

#ifdef NETSNMP_CACHE_AUTO_RELOAD
    netsnmp_cache *stats_table_cache = NULL;
#endif

    if (ops_handler || entries_handler || entity_handler) {
        snmp_log(LOG_ERR, "initialize_stats_table called more than once.\n");
        return;
    }

    memset(&ops_cb, 0x00, sizeof(ops_cb));
    memset(&entries_cb, 0x00, sizeof(entries_cb));
    memset(&entity_cb, 0x00, sizeof(entity_cb));


    ops_table_info = SNMP_MALLOC_TYPEDEF(netsnmp_table_registration_info);
    entries_table_info = SNMP_MALLOC_TYPEDEF(netsnmp_table_registration_info);
    entity_table_info = SNMP_MALLOC_TYPEDEF(netsnmp_table_registration_info);


    ops_handler = netsnmp_create_handler_registration("dsOpsTable",
                                                     netsnmp_table_array_helper_handler,
                                                     dsOpsTable_oid,
                                                     dsOpsTable_oid_len,
                                                     HANDLER_CAN_RONLY);
    entries_handler = netsnmp_create_handler_registration("dsEntriesTable",
                                                     netsnmp_table_array_helper_handler,
                                                     dsEntriesTable_oid,
                                                     dsEntriesTable_oid_len,
                                                     HANDLER_CAN_RONLY);
    entity_handler = netsnmp_create_handler_registration("dsEntityTable",
                                                     netsnmp_table_array_helper_handler,
                                                     dsEntityTable_oid,
                                                     dsEntityTable_oid_len,
                                                     HANDLER_CAN_RONLY);

    if (!ops_handler || !entries_handler || !entity_handler ||
        !ops_table_info || !entries_table_info || !entity_table_info) {

        snmp_log(LOG_ERR, "malloc failed in initialize_stats_table\n");
        SNMP_FREE(ops_table_info);
        SNMP_FREE(entries_table_info);
        SNMP_FREE(entity_table_info);
        return;
    }


    netsnmp_table_helper_add_index(ops_table_info, ASN_INTEGER);
    netsnmp_table_helper_add_index(entries_table_info, ASN_INTEGER);
    netsnmp_table_helper_add_index(entity_table_info, ASN_INTEGER);

    ops_table_info->min_column = dsOpsTable_COL_MIN;
    ops_table_info->max_column = dsOpsTable_COL_MAX;
    entries_table_info->min_column = dsEntriesTable_COL_MIN;
    entries_table_info->max_column = dsEntriesTable_COL_MAX;
    entity_table_info->min_column = dsEntityTable_COL_MIN;
    entity_table_info->max_column = dsEntityTable_COL_MAX;


    ops_cb.get_value = dsOpsTable_get_value;
    ops_cb.container = netsnmp_container_find("dsOpsTable_primary:"
                                          "dsOpsTable:" "table_container");
    entries_cb.get_value = dsEntriesTable_get_value;
    entries_cb.container = ops_cb.container;
    entity_cb.get_value = dsEntityTable_get_value;
    entity_cb.container = ops_cb.container;


    netsnmp_table_container_register(ops_handler, ops_table_info, &ops_cb,
                                     ops_cb.container, 1);
    netsnmp_table_container_register(entries_handler, entries_table_info, &entries_cb,
                                     entries_cb.container, 1);
    netsnmp_table_container_register(entity_handler, entity_table_info, &entity_cb,
                                     entity_cb.container, 1);


#ifdef NETSNMP_CACHE_AUTO_RELOAD

    stats_table_cache = netsnmp_cache_create(CACHE_REFRESH_INTERVAL, load_stats_table,
                                            NULL, dsOpsTable_oid, dsOpsTable_oid_len);
    stats_table_cache->flags |= NETSNMP_CACHE_DONT_FREE_EXPIRED;
    stats_table_cache->flags |= NETSNMP_CACHE_DONT_AUTO_RELEASE;
    stats_table_cache->flags |= NETSNMP_CACHE_AUTO_RELOAD;
    netsnmp_inject_handler(ops_handler, netsnmp_cache_handler_get(stats_table_cache));
#else

    netsnmp_inject_handler(ops_handler, netsnmp_get_cache_handler(CACHE_REFRESH_INTERVAL, load_stats_table,
                                            free_stats_table, dsOpsTable_oid, dsOpsTable_oid_len));
#endif
}
