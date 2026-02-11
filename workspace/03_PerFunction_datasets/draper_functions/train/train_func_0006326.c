ipAddressIfIndex_undo(ipAddressTable_rowreq_ctx * rowreq_ctx)
{

    DEBUGMSGTL(("verbose:ipAddressTable:ipAddressIfIndex_undo",
                "called\n"));

    netsnmp_assert(NULL != rowreq_ctx);


    rowreq_ctx->data->if_index = rowreq_ctx->undo->if_index;

    return MFD_SUCCESS;
}
