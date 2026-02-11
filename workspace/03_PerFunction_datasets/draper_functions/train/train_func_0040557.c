_tcpListenerTable_get_column(tcpListenerTable_rowreq_ctx * rowreq_ctx,
                             netsnmp_variable_list * var, int column)
{
    int             rc = SNMPERR_SUCCESS;

    DEBUGMSGTL(("internal:tcpListenerTable:_mfd_tcpListenerTable_get_column", "called for %d\n", column));


    netsnmp_assert(NULL != rowreq_ctx);

    switch (column) {


    case COLUMN_TCPLISTENERPROCESS:
        var->val_len = sizeof(u_long);
        var->type = ASN_UNSIGNED;
        rc = tcpListenerProcess_get(rowreq_ctx,
                                    (u_long *) var->val.string);
        break;

    default:
        snmp_log(LOG_ERR,
                 "unknown column %d in _tcpListenerTable_get_column\n",
                 column);
        break;
    }

    return rc;
}
