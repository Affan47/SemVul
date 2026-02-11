ipCidrRouteAge_get(ipCidrRouteTable_rowreq_ctx * rowreq_ctx,
                   long *ipCidrRouteAge_val_ptr)
{

    netsnmp_assert(NULL != ipCidrRouteAge_val_ptr);


    DEBUGMSGTL(("verbose:ipCidrRouteTable:ipCidrRouteAge_get",
                "called\n"));

    netsnmp_assert(NULL != rowreq_ctx);


    return MFD_SKIP;

    return MFD_SUCCESS;
}
