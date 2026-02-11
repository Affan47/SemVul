_mfd_ifXTable_undo_values(netsnmp_mib_handler *handler,
                          netsnmp_handler_registration *reginfo,
                          netsnmp_agent_request_info *agtreq_info,
                          netsnmp_request_info *requests)
{
    int             rc;
    ifXTable_rowreq_ctx *rowreq_ctx = (ifXTable_rowreq_ctx*)
        netsnmp_container_table_row_extract(requests);
    netsnmp_table_request_info *tri;

    DEBUGMSGTL(("internal:ifXTable:_mfd_ifXTable_undo_values",
                "called\n"));

    netsnmp_assert(NULL != rowreq_ctx);

    rc = ifXTable_undo(rowreq_ctx);
    if (MFD_SUCCESS != rc) {


        DEBUGMSGTL(("ifXTable:mfd", "error %d from "
                    "ifXTable_undo\n", rc));
    }

    for (; requests; requests = requests->next) {


        tri = netsnmp_extract_table_info(requests);
        if (NULL == tri)
            continue;

        rc = _ifXTable_undo_column(rowreq_ctx, requests->requestvb,
                                   tri->colnum);
        if (MFD_SUCCESS != rc) {


            DEBUGMSGTL(("ifXTable:mfd", "error %d from "
                        "ifXTable_undo_column\n", rc));
        }
    }

    return SNMP_ERR_NOERROR;
}
