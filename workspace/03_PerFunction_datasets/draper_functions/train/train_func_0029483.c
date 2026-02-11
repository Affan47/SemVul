clear_mteETable(int majorID, int minorID, void *serverarg, void *clientarg)
{
    netsnmp_tdata_row    *row;
    netsnmp_variable_list owner_var;


    memset( &owner_var, 0, sizeof(netsnmp_variable_list));
    snmp_set_var_typed_value( &owner_var,  ASN_OCTET_STR,
                             "snmpd.conf", strlen("snmpd.conf"));
    while (( row = netsnmp_tdata_row_next_byidx( event_table_data,
                                                &owner_var ))) {


        netsnmp_tdata_remove_and_delete_row( event_table_data, row );
    }
    return SNMPERR_SUCCESS;
}
