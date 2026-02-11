initialize_table_hrSWInstalledTable(void)
{
    static oid      hrSWInstalledTable_oid[] =
        { 1, 3, 6, 1, 2, 1, 25, 6, 3 };
    size_t          hrSWInstalledTable_oid_len =
        OID_LENGTH(hrSWInstalledTable_oid);
    netsnmp_handler_registration *reg;
    netsnmp_mib_handler *handler = NULL;
    netsnmp_container *container = NULL;
    netsnmp_cache *cache = NULL;

    DEBUGMSGTL(("hrSWInstalled", "initialize\n"));

    reg =
        netsnmp_create_handler_registration("hrSWInstalledTable",
                                            hrSWInstalledTable_handler,
                                            hrSWInstalledTable_oid,
                                            hrSWInstalledTable_oid_len,
                                            HANDLER_CAN_RONLY);
    if (NULL == reg) {
        snmp_log(LOG_ERR,"error creating handler registration for "
                 MYTABLE "\n");
        goto bail;
    }

    container = netsnmp_container_find("hrSWInstalledTable:table_container");
    if (NULL == container) {
        snmp_log(LOG_ERR,"error creating container for "
                 MYTABLE "\n");
        goto bail;
    }

    table_info = SNMP_MALLOC_TYPEDEF(netsnmp_table_registration_info);
    if (NULL == table_info) {
        snmp_log(LOG_ERR,"error allocating table registration for "
                 MYTABLE "\n");
        goto bail;
    }

    netsnmp_table_helper_add_indexes(table_info, ASN_INTEGER,
                                     0);
    table_info->min_column = COLUMN_HRSWINSTALLEDINDEX;
    table_info->max_column = COLUMN_HRSWINSTALLEDDATE;


    handler = netsnmp_container_table_handler_get(table_info, container,
                                                  TABLE_CONTAINER_KEY_NETSNMP_INDEX);
    if (NULL == handler) {
        snmp_log(LOG_ERR,"error allocating table registration for "
                 MYTABLE "\n");
        goto bail;
    }
    if (SNMPERR_SUCCESS != netsnmp_inject_handler(reg, handler)) {
        snmp_log(LOG_ERR,"error injecting container_table handler for "
                 MYTABLE "\n");
        goto bail;
    }
    handler = NULL;


    cache = netsnmp_cache_create(30,
                                 _cache_load, _cache_free,
                                 hrSWInstalledTable_oid,
                                 hrSWInstalledTable_oid_len);

    if (NULL == cache) {
        snmp_log(LOG_ERR, "error creating cache for "
                 MYTABLE "\n");
        goto bail;
    }
    cache->magic = container;

    handler = netsnmp_cache_handler_get(cache);
    if (NULL == handler) {
        snmp_log(LOG_ERR, "error creating cache handler for "
                 MYTABLE "\n");
        goto bail;
    }
    if (SNMPERR_SUCCESS != netsnmp_inject_handler(reg, handler)) {
        snmp_log(LOG_ERR,"error injecting cache handler for "
                 MYTABLE "\n");
        goto bail;
    }
    handler = NULL;

    if (SNMPERR_SUCCESS != netsnmp_register_table(reg, table_info)) {
        snmp_log(LOG_ERR,"error registering table handler for "
                 MYTABLE "\n");
        goto bail;
    }

    return;


  bail:

    if (handler)
        netsnmp_handler_free(handler);

    if (cache)
        netsnmp_cache_free(cache);

    if (table_info)
        netsnmp_table_registration_info_free(table_info);

    if (container)
        CONTAINER_FREE(container);

    if (reg)
        netsnmp_handler_registration_free(reg);

}
