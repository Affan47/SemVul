_mfd_ipAddressTable_undo_cleanup(netsnmp_mib_handler *handler,
                                 netsnmp_handler_registration *reginfo,
                                 netsnmp_agent_request_info *agtreq_info,
                                 netsnmp_request_info *requests)
{
    ipAddressTable_rowreq_ctx *rowreq_ctx = (ipAddressTable_rowreq_ctx*)
        netsnmp_container_table_row_extract(requests);
    int             rc;

    DEBUGMSGTL(("internal:ipAddressTable:_mfd_ipAddressTable_undo_cleanup",
                "called\n"));


    if (NULL == rowreq_ctx)
        return MFD_SUCCESS;


    rc = ipAddressTable_undo_cleanup(rowreq_ctx);
    if (MFD_SUCCESS != rc) {


        DEBUGMSGTL(("ipAddressTable:mfd", "error %d from "
                    "ipAddressTable_undo_cleanup\n", rc));
    }


    if (rowreq_ctx->undo) {
        ipAddressTable_release_data(rowreq_ctx->undo);
        rowreq_ctx->undo = NULL;
    }


    return SNMP_ERR_NOERROR;
}
