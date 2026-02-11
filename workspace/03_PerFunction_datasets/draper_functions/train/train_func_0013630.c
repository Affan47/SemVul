_snmpNotifyFilterTable_container_row_restore(const char *token, char *buf)
{
    snmpNotifyFilterTable_rowreq_ctx *rowreq_ctx;
    netsnmp_index   index;
    oid             tmp_oid[MAX_snmpNotifyFilterTable_IDX_LEN];
    u_int           col = 0, found = 0;


    if (strncmp(token, row_token, sizeof(row_token)) != 0) {
        snmp_log(LOG_ERR,
                 "unknown token in _snmpNotifyFilterTable_container_row_restore\n");
        return;
    }

    DEBUGMSGTL(("internal:snmpNotifyFilterTable:_snmpNotifyFilterTable_container_row_restore", "parsing line '%s'\n", buf));


    index.oids = tmp_oid;
    index.len = OID_LENGTH(tmp_oid);
    buf = read_config_read_objid(buf, &index.oids, &index.len);
    if (NULL == buf) {
        snmp_log(LOG_ERR, "error reading row index in "
                 "_snmpNotifyFilterTable_container_row_restore\n");
        return;
    }
    rowreq_ctx =
        _mfd_snmpNotifyFilterTable_rowreq_from_index(&index, NULL);
    if (NULL == rowreq_ctx) {
        snmp_log(LOG_ERR, "error creating row index in "
                 "_snmpNotifyFilterTable_container_row_restore\n");
        return;
    }


    buf = skip_white(buf);
    while ((NULL != buf) && isdigit((unsigned char)(*buf))) {


        col = (u_int) strtol(buf, &buf, 10);
        if (NULL == buf)
            break;
        if (*buf != ':') {
            buf = NULL;
            break;
        }
        ++buf;


        DEBUGMSGTL(("_snmpNotifyFilterTable_container_row_restore",
                    "parsing column %d\n", col));
        buf =
            _snmpNotifyFilterTable_container_col_restore(rowreq_ctx, col,
                                                         buf);
        ++found;
    }
    if (0 == found) {
        snmp_log(LOG_ERR,
                 "error parsing snmpNotifyFilterTable row; no columns found");
        snmpNotifyFilterTable_release_rowreq_ctx(rowreq_ctx);
        return;
    }


    if ((buf == NULL) || (*buf != LINE_TERM_CHAR)) {
        snmp_log(LOG_ERR,
                 "error parsing snmpNotifyFilterTable row around column %d",
                 col);
        snmpNotifyFilterTable_release_rowreq_ctx(rowreq_ctx);
        return;
    }

    DEBUGMSGTL(("internal:snmpNotifyFilterTable:_snmpNotifyFilterTable_container_row_restore", "inserting row\n"));


    rowreq_ctx->oid_idx.len = index.len;
    memcpy(rowreq_ctx->oid_idx.oids, index.oids, index.len * sizeof(oid));

    CONTAINER_INSERT(snmpNotifyFilterTable_if_ctx.container, rowreq_ctx);
}
