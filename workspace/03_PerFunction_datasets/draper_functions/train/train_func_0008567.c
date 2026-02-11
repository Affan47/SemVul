init_snmpNotifyFilterProfileTable(void)
{
    DEBUGMSGTL(("snmpNotifyFilterProfileTable", "initializing...  "));


    REGISTER_MIB("snmpNotifyFilterProfileTable",
                 snmpNotifyFilterProfileTable_variables, variable2,
                 snmpNotifyFilterProfileTable_variables_oid);


    snmpd_register_config_handler("snmpNotifyFilterProfileTable",
                                  parse_snmpNotifyFilterProfileTable, NULL,
                                  NULL);


    snmp_register_callback(SNMP_CALLBACK_LIBRARY, SNMP_CALLBACK_STORE_DATA,
                           store_snmpNotifyFilterProfileTable, NULL);


    DEBUGMSGTL(("snmpNotifyFilterProfileTable", "done.\n"));
}
