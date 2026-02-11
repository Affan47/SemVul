_mfd_ifTable_undo_setup(netsnmp_mib_handler *handler,
                        netsnmp_handler_registration *reginfo,
                        netsnmp_agent_request_info *agtreq_info,
                        netsnmp_request_info *requests)
{
    int             rc;
    ifTable_rowreq_ctx *rowreq_ctx = (ifTable_rowreq_ctx*)
        netsnmp_container_table_row_extract(requests);

    DEBUGMSGTL(("internal:ifTable:_mfd_ifTable_undo_setup", "called\n"));

    netsnmp_assert(NULL != rowreq_ctx);


    rc = _mfd_ifTable_undo_setup_allocate(rowreq_ctx);
    if (MFD_SUCCESS != rc) {
        netsnmp_request_set_error_all(requests, rc);
        return SNMP_ERR_NOERROR;
    }


    rc = ifTable_undo_setup(rowreq_ctx);
    if (MFD_SUCCESS != rc) {
        DEBUGMSGTL(("ifTable:mfd", "error %d from "
                    "ifTable_undo_setup\n", rc));
        netsnmp_request_set_error_all(requests, SNMP_VALIDATE_ERR(rc));
    } else {


        netsnmp_table_request_info *tri;
        for (; requests; requests = requests->next) {


            tri = netsnmp_extract_table_info(requests);
            if (NULL == tri)
                continue;

            rc = _ifTable_undo_setup_column(rowreq_ctx, tri->colnum);
            if (MFD_SUCCESS != rc) {
                DEBUGMSGTL(("ifTable:mfd", "error %d from "
                            "ifTable_undo_setup_column\n", rc));
                netsnmp_set_request_error(agtreq_info, requests,
                                          SNMP_VALIDATE_ERR(rc));
            }
        }
    }

    return SNMP_ERR_NOERROR;
}
