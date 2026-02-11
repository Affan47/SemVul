ipAddressStatus_check_value(ipAddressTable_rowreq_ctx * rowreq_ctx,
                            u_long ipAddressStatus_val)
{
    DEBUGMSGTL(("verbose:ipAddressTable:ipAddressStatus_check_value",
                "called\n"));


    netsnmp_assert(NULL != rowreq_ctx);


    if (IPADDRESSSTATUSTC_PREFERRED != ipAddressStatus_val)
        return MFD_NOT_VALID_EVER;

    return MFD_SUCCESS;
}
