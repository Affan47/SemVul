_ipCidrRouteTable_initialize_interface(ipCidrRouteTable_registration *
                                       reg_ptr, u_long flags)
{
    netsnmp_baby_steps_access_methods *access_multiplexer =
        &ipCidrRouteTable_if_ctx.access_multiplexer;
    netsnmp_table_registration_info *tbl_info =
        &ipCidrRouteTable_if_ctx.tbl_info;
    netsnmp_handler_registration *reginfo;
    netsnmp_mib_handler *handler;
    int             mfd_modes = 0;

    DEBUGMSGTL(("internal:ipCidrRouteTable:_ipCidrRouteTable_initialize_interface", "called\n"));


    netsnmp_table_helper_add_indexes(tbl_info, ASN_IPADDRESS,

                                     ASN_IPADDRESS,

                                     ASN_INTEGER,

                                     ASN_IPADDRESS,

                                     0);


    tbl_info->min_column = IPCIDRROUTETABLE_MIN_COL;
    tbl_info->max_column = IPCIDRROUTETABLE_MAX_COL;


    ipCidrRouteTable_if_ctx.user_ctx = reg_ptr;


    ipCidrRouteTable_init_data(reg_ptr);


    _ipCidrRouteTable_container_init(&ipCidrRouteTable_if_ctx);
    if (NULL == ipCidrRouteTable_if_ctx.container) {
        snmp_log(LOG_ERR,
                 "could not initialize container for ipCidrRouteTable\n");
        return;
    }


    access_multiplexer->object_lookup =
        _mfd_ipCidrRouteTable_object_lookup;
    access_multiplexer->get_values = _mfd_ipCidrRouteTable_get_values;


    access_multiplexer->pre_request = _mfd_ipCidrRouteTable_pre_request;
    access_multiplexer->post_request = _mfd_ipCidrRouteTable_post_request;


#if !(defined(NETSNMP_NO_WRITE_SUPPORT) || defined(NETSNMP_DISABLE_SET_SUPPORT))


    access_multiplexer->object_syntax_checks =
        _mfd_ipCidrRouteTable_check_objects;
    access_multiplexer->undo_setup = _mfd_ipCidrRouteTable_undo_setup;
    access_multiplexer->undo_cleanup = _mfd_ipCidrRouteTable_undo_cleanup;
    access_multiplexer->set_values = _mfd_ipCidrRouteTable_set_values;
    access_multiplexer->undo_sets = _mfd_ipCidrRouteTable_undo_values;


    access_multiplexer->commit = _mfd_ipCidrRouteTable_commit;
    access_multiplexer->undo_commit = _mfd_ipCidrRouteTable_undo_commit;
    access_multiplexer->irreversible_commit =
        _mfd_ipCidrRouteTable_irreversible_commit;
#endif


    DEBUGMSGTL(("ipCidrRouteTable:init_ipCidrRouteTable",
                "Registering ipCidrRouteTable as a mibs-for-dummies table.\n"));
    handler =
        netsnmp_baby_steps_access_multiplexer_get(access_multiplexer);
    reginfo =
        netsnmp_handler_registration_create("ipCidrRouteTable", handler,
                                            ipCidrRouteTable_oid,
                                            ipCidrRouteTable_oid_size,
                                            HANDLER_CAN_BABY_STEP |
                                            HANDLER_CAN_RONLY);
    if (NULL == reginfo) {
        snmp_log(LOG_ERR, "error registering table ipCidrRouteTable\n");
        return;
    }
    reginfo->my_reg_void = &ipCidrRouteTable_if_ctx;


    if (access_multiplexer->object_lookup)
        mfd_modes |= BABY_STEP_OBJECT_LOOKUP;
    if (access_multiplexer->pre_request)
        mfd_modes |= BABY_STEP_PRE_REQUEST;
    if (access_multiplexer->post_request)
        mfd_modes |= BABY_STEP_POST_REQUEST;

#if !(defined(NETSNMP_NO_WRITE_SUPPORT) || defined(NETSNMP_DISABLE_SET_SUPPORT))
    if (access_multiplexer->set_values)
        mfd_modes |= BABY_STEP_SET_VALUES;
    if (access_multiplexer->irreversible_commit)
        mfd_modes |= BABY_STEP_IRREVERSIBLE_COMMIT;
    if (access_multiplexer->object_syntax_checks)
        mfd_modes |= BABY_STEP_CHECK_OBJECT;

    if (access_multiplexer->undo_setup)
        mfd_modes |= BABY_STEP_UNDO_SETUP;
    if (access_multiplexer->undo_cleanup)
        mfd_modes |= BABY_STEP_UNDO_CLEANUP;
    if (access_multiplexer->undo_sets)
        mfd_modes |= BABY_STEP_UNDO_SETS;

    if (access_multiplexer->row_creation)
        mfd_modes |= BABY_STEP_ROW_CREATE;
    if (access_multiplexer->consistency_checks)
        mfd_modes |= BABY_STEP_CHECK_CONSISTENCY;
    if (access_multiplexer->commit)
        mfd_modes |= BABY_STEP_COMMIT;
    if (access_multiplexer->undo_commit)
        mfd_modes |= BABY_STEP_UNDO_COMMIT;
#endif

    handler = netsnmp_baby_steps_handler_get(mfd_modes);
    netsnmp_inject_handler(reginfo, handler);


    handler = netsnmp_get_row_merge_handler(reginfo->rootoid_len + 2);
    netsnmp_inject_handler(reginfo, handler);


    handler =
        netsnmp_container_table_handler_get(tbl_info,
                                            ipCidrRouteTable_if_ctx.
                                            container,
                                            TABLE_CONTAINER_KEY_NETSNMP_INDEX);
    netsnmp_inject_handler(reginfo, handler);


    if (NULL != ipCidrRouteTable_if_ctx.cache) {
        handler = netsnmp_cache_handler_get(ipCidrRouteTable_if_ctx.cache);
        netsnmp_inject_handler(reginfo, handler);
    }


    netsnmp_register_table(reginfo, tbl_info);

}
