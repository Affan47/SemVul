ipAddressTable_commit(ipAddressTable_rowreq_ctx * rowreq_ctx)
{
    int             rc = MFD_SUCCESS;

    DEBUGMSGTL(("verbose:ipAddressTable:ipAddressTable_commit",
                "called\n"));


    netsnmp_assert(NULL != rowreq_ctx);


    if (0 == rowreq_ctx->column_set_flags) {
        DEBUGMSGTL(("ipAddressTable:ipAddressTable_commit",
                    "no change\n"));
        return MFD_SUCCESS;
    }


    rowreq_ctx->data->flags = rowreq_ctx->column_set_flags;

    if (rowreq_ctx->column_set_flags & COLUMN_IPADDRESSROWSTATUS_FLAG) {
        if (rowreq_ctx->rowreq_flags & MFD_ROW_CREATED) {
            rowreq_ctx->data->flags |= NETSNMP_ACCESS_IPADDRESS_CREATE;
            rowreq_ctx->ipAddressCreated = netsnmp_get_agent_uptime();
        } else if (ROWSTATUS_DESTROY == rowreq_ctx->ipAddressRowStatus) {
            rowreq_ctx->data->flags |= NETSNMP_ACCESS_IPADDRESS_DELETE;
        } else
            rowreq_ctx->data->flags |= NETSNMP_ACCESS_IPADDRESS_CHANGE;
    } else
        rowreq_ctx->data->flags |= NETSNMP_ACCESS_IPADDRESS_CHANGE;


    rc = netsnmp_access_ipaddress_entry_set(rowreq_ctx->data);
    if (rc) {
        DEBUGMSGTL(("ipAddressTable",
                    "bad rc %d from IP address data access\n", rc));
        rc = MFD_ERROR;
    } else {
        rowreq_ctx->ipAddressLastChanged = netsnmp_get_agent_uptime();
    }


    if (MFD_SUCCESS == rc) {
        rowreq_ctx->rowreq_flags |= MFD_ROW_DIRTY;
    }

    return rc;
}
