netsnmp_update_variable_list_from_index(netsnmp_table_request_info *tri)
{
    if (!tri)
        return SNMPERR_GENERR;


    snmp_reset_var_buffers( tri->indexes);

    return parse_oid_indexes(tri->index_oid, tri->index_oid_len,
                             tri->indexes);
}
