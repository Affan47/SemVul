_inetNetToMediaTable_check_indexes(inetNetToMediaTable_rowreq_ctx *
                                   rowreq_ctx)
{
    int             rc = SNMPERR_SUCCESS;

    DEBUGMSGTL(("internal:inetNetToMediaTable:_inetNetToMediaTable_check_indexes", "called\n"));

    netsnmp_assert(NULL != rowreq_ctx);


    if ((SNMPERR_SUCCESS == rc)
        && ((rowreq_ctx->tbl_idx.inetNetToMediaIfIndex < 1)
            || (rowreq_ctx->tbl_idx.inetNetToMediaIfIndex > 2147483647))
        ) {
        rc = SNMP_ERR_WRONGVALUE;
    }
    if (MFD_SUCCESS != rc)
        return rc;
    rc = inetNetToMediaIfIndex_check_index(rowreq_ctx);
    if (MFD_SUCCESS != rc)
        return SNMP_ERR_NOCREATION;


    if ((SNMPERR_SUCCESS == rc)
        && (rowreq_ctx->tbl_idx.inetNetToMediaNetAddressType !=
            INETADDRESSTYPE_UNKNOWN)
        && (rowreq_ctx->tbl_idx.inetNetToMediaNetAddressType !=
            INETADDRESSTYPE_IPV4)
        && (rowreq_ctx->tbl_idx.inetNetToMediaNetAddressType !=
            INETADDRESSTYPE_IPV6)
        && (rowreq_ctx->tbl_idx.inetNetToMediaNetAddressType !=
            INETADDRESSTYPE_IPV4Z)
        && (rowreq_ctx->tbl_idx.inetNetToMediaNetAddressType !=
            INETADDRESSTYPE_IPV6Z)
        && (rowreq_ctx->tbl_idx.inetNetToMediaNetAddressType !=
            INETADDRESSTYPE_DNS)
        ) {
        rc = SNMP_ERR_WRONGVALUE;
    }
    if (MFD_SUCCESS != rc)
        return rc;
    rc = inetNetToMediaNetAddressType_check_index(rowreq_ctx);
    if (MFD_SUCCESS != rc)
        return SNMP_ERR_NOCREATION;


    if ((SNMPERR_SUCCESS == rc)
        && ((rowreq_ctx->tbl_idx.inetNetToMediaNetAddress_len < 0)
            || (rowreq_ctx->tbl_idx.inetNetToMediaNetAddress_len > 255))
        ) {
        rc = SNMP_ERR_WRONGLENGTH;
    }
    if (MFD_SUCCESS != rc)
        return rc;
    rc = inetNetToMediaNetAddress_check_index(rowreq_ctx);
    if (MFD_SUCCESS != rc)
        return SNMP_ERR_NOCREATION;


    return inetNetToMediaTable_validate_index(inetNetToMediaTable_if_ctx.
                                              user_ctx, rowreq_ctx);
}
