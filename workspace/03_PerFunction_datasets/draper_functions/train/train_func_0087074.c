send_DirectoryServerStart_trap(server_instance *serv_p)
{
    netsnmp_variable_list *var_list = NULL;
    stats_table_context *ctx = NULL;


    oid DirectoryServerStart_oid[] = { DirectoryServerStart_OID };
    oid dsEntityDescr_oid[] = { dsEntityTable_TABLE_OID, 1, COLUMN_DSENTITYDESCR, 0 };
    oid dsEntityVers_oid[] = { dsEntityTable_TABLE_OID, 1, COLUMN_DSENTITYVERS, 0 };
    oid dsEntityLocation_oid[] = { dsEntityTable_TABLE_OID, 1, COLUMN_DSENTITYLOCATION, 0 };

    dsEntityDescr_oid[3] = serv_p->port;
    dsEntityVers_oid[3] = serv_p->port;
    dsEntityLocation_oid[3] = serv_p->port;

    snmp_log(LOG_INFO, "Sending start trap for server: %d\n", serv_p->port);


    if ((ctx = stats_table_find_row(serv_p->port)) == NULL) {
        snmp_log(LOG_ERR, "Malloc error finding row for server: %d\n", serv_p->port);
        return 1;
    }


    snmp_varlist_add_variable(&var_list,
                              snmptrap_oid, OID_LENGTH(snmptrap_oid),
                              ASN_OBJECT_ID,
                              (u_char *) &DirectoryServerStart_oid,
                              sizeof(DirectoryServerStart_oid));
    snmp_varlist_add_variable(&var_list,
                              dsEntityDescr_oid,
                              OID_LENGTH(dsEntityDescr_oid), ASN_OCTET_STR,
                              (u_char *) ctx->hdr_tbl.dsDescription,
                              strlen(ctx->hdr_tbl.dsDescription));
    snmp_varlist_add_variable(&var_list,
                              dsEntityVers_oid,
                              OID_LENGTH(dsEntityVers_oid), ASN_OCTET_STR,
                              (u_char *) ctx->hdr_tbl.dsVersion,
                              strlen(ctx->hdr_tbl.dsVersion));
    snmp_varlist_add_variable(&var_list,
                              dsEntityLocation_oid,
                              OID_LENGTH(dsEntityLocation_oid),
                              ASN_OCTET_STR,
                              (u_char *) ctx->hdr_tbl.dsLocation,
                              strlen(ctx->hdr_tbl.dsLocation));


    send_v2trap(var_list);
    snmp_free_varbind(var_list);

    return SNMP_ERR_NOERROR;
}
