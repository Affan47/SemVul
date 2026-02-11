ipAddressTable_undo_cleanup(ipAddressTable_rowreq_ctx * rowreq_ctx)
{
    int             rc = MFD_SUCCESS;

    DEBUGMSGTL(("verbose:ipAddressTable:ipAddressTable_undo_cleanup",
                "called\n"));


    netsnmp_assert(NULL != rowreq_ctx);


    rowreq_ctx->ipAddressLastChanged =
        rowreq_ctx->ipAddressLastChanged_undo;

    return rc;
}
