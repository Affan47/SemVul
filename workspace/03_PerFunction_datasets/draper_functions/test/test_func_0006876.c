_ifTable_set_column(ifTable_rowreq_ctx * rowreq_ctx,
                    netsnmp_variable_list * var, int column)
{
    int             rc = SNMPERR_SUCCESS;

    DEBUGMSGTL(("internal:ifTable:_ifTable_set_column",
                "called for %d\n", column));

    netsnmp_assert(NULL != rowreq_ctx);

    switch (column) {


    case COLUMN_IFADMINSTATUS:
        rowreq_ctx->column_set_flags |= COLUMN_IFADMINSTATUS_FLAG;
        rc = ifAdminStatus_set(rowreq_ctx, *((u_long *) var->val.string));
        break;

    default:
        snmp_log(LOG_ERR, "unknown column %d in _ifTable_set_column\n",
                 column);
        rc = SNMP_ERR_GENERR;
        break;
    }

    return rc;
}
