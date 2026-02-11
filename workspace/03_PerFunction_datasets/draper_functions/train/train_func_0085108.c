_add_connection(netsnmp_tcpconn_entry *entry, netsnmp_container *container)
{
    tcpListenerTable_rowreq_ctx *rowreq_ctx;

    DEBUGMSGTL(("tcpListenerTable:access", "creating new entry\n"));


    rowreq_ctx = tcpListenerTable_allocate_rowreq_ctx(entry, NULL);
    if ((NULL != rowreq_ctx) &&
        (MFD_SUCCESS == tcpListenerTable_indexes_set(rowreq_ctx,
                                                     entry->loc_addr_len,
                                                     (char *) entry->loc_addr,
                                                     entry->loc_addr_len,
                                                     entry->loc_port))) {
        CONTAINER_INSERT(container, rowreq_ctx);
    } else {
        if (rowreq_ctx) {
            snmp_log(LOG_ERR, "error setting index while loading "
                     "tcpListenerTable cache.\n");
            tcpListenerTable_release_rowreq_ctx(rowreq_ctx);
        } else {
            snmp_log(LOG_ERR, "memory allocation failed while loading "
                     "tcpListenerTable cache.\n");
            netsnmp_access_tcpconn_entry_free(entry);
        }
    }
}
