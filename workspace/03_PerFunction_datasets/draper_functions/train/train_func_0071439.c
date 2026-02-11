ipIfStatsTable_index_from_oid(netsnmp_index * oid_idx,
                              ipIfStatsTable_mib_index * mib_idx)
{
    int             err = SNMP_ERR_NOERROR;


    netsnmp_variable_list var_ipIfStatsIPVersion;


    netsnmp_variable_list var_ipIfStatsIfIndex;


    memset(&var_ipIfStatsIPVersion, 0x00, sizeof(var_ipIfStatsIPVersion));
    var_ipIfStatsIPVersion.type = ASN_INTEGER;
    memset(&var_ipIfStatsIfIndex, 0x00, sizeof(var_ipIfStatsIfIndex));
    var_ipIfStatsIfIndex.type = ASN_INTEGER;


    var_ipIfStatsIPVersion.next_variable = &var_ipIfStatsIfIndex;
    var_ipIfStatsIfIndex.next_variable = NULL;


    DEBUGMSGTL(("verbose:ipIfStatsTable:ipIfStatsTable_index_from_oid",
                "called\n"));


    err = parse_oid_indexes(oid_idx->oids, oid_idx->len,
                            &var_ipIfStatsIPVersion);
    if (err == SNMP_ERR_NOERROR) {


        mib_idx->ipIfStatsIPVersion =
            *((u_long *) var_ipIfStatsIPVersion.val.string);
        mib_idx->ipIfStatsIfIndex =
            *((long *) var_ipIfStatsIfIndex.val.string);


    }


    snmp_reset_var_buffers(&var_ipIfStatsIPVersion);

    return err;
}
