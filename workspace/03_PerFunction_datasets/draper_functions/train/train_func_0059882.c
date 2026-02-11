inetCidrRouteStatus_set(inetCidrRouteTable_rowreq_ctx * rowreq_ctx,
                        u_long inetCidrRouteStatus_val)
{

    DEBUGMSGTL(("verbose:inetCidrRouteTable:inetCidrRouteStatus_set",
                "called\n"));


    netsnmp_assert(NULL != rowreq_ctx);


    rowreq_ctx->row_status = inetCidrRouteStatus_val;

    return MFD_SUCCESS;
}
