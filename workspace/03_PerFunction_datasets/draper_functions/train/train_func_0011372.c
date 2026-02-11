snmpNotifyFilterTable_index_from_oid(netsnmp_index * oid_idx,
                                     snmpNotifyFilterTable_mib_index *
                                     mib_idx)
{
    int             err = SNMP_ERR_NOERROR;


    netsnmp_variable_list var_snmpNotifyFilterProfileName;


    netsnmp_variable_list var_snmpNotifyFilterSubtree;


    memset(&var_snmpNotifyFilterProfileName, 0x00,
           sizeof(var_snmpNotifyFilterProfileName));
    var_snmpNotifyFilterProfileName.type = ASN_OCTET_STR;
    memset(&var_snmpNotifyFilterSubtree, 0x00,
           sizeof(var_snmpNotifyFilterSubtree));
    var_snmpNotifyFilterSubtree.type = ASN_PRIV_IMPLIED_OBJECT_ID;


    var_snmpNotifyFilterProfileName.next_variable =
        &var_snmpNotifyFilterSubtree;
    var_snmpNotifyFilterSubtree.next_variable = NULL;


    DEBUGMSGTL(("verbose:snmpNotifyFilterTable:snmpNotifyFilterTable_index_from_oid", "called\n"));


    err = parse_oid_indexes(oid_idx->oids, oid_idx->len,
                            &var_snmpNotifyFilterProfileName);
    if (err == SNMP_ERR_NOERROR) {


        if (var_snmpNotifyFilterProfileName.val_len >
            sizeof(mib_idx->snmpNotifyFilterProfileName))
            err = SNMP_ERR_GENERR;
        else {
            memcpy(mib_idx->snmpNotifyFilterProfileName,
                   var_snmpNotifyFilterProfileName.val.string,
                   var_snmpNotifyFilterProfileName.val_len);
            mib_idx->snmpNotifyFilterProfileName_len =
                var_snmpNotifyFilterProfileName.val_len /
                sizeof(mib_idx->snmpNotifyFilterProfileName[0]);
        }


        if (var_snmpNotifyFilterSubtree.val_len >
            sizeof(mib_idx->snmpNotifyFilterSubtree))
            err = SNMP_ERR_GENERR;
        else {
            memcpy(mib_idx->snmpNotifyFilterSubtree,
                   var_snmpNotifyFilterSubtree.val.string,
                   var_snmpNotifyFilterSubtree.val_len);
            mib_idx->snmpNotifyFilterSubtree_len =
                var_snmpNotifyFilterSubtree.val_len /
                sizeof(mib_idx->snmpNotifyFilterSubtree[0]);
        }


    }


    snmp_reset_var_buffers(&var_snmpNotifyFilterProfileName);

    return err;
}
