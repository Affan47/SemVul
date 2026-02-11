netsnmp_config(char *line)
{
    int             ret = SNMP_ERR_NOERROR;
    DEBUGMSGTL(("snmp_config", "remembering line \"%s\"\n", line));
    netsnmp_config_remember(line);


    if (netsnmp_ds_get_boolean(NETSNMP_DS_LIBRARY_ID,
			       NETSNMP_DS_LIB_HAVE_READ_CONFIG)) {
        DEBUGMSGTL(("snmp_config", "  ... processing it now\n"));
        ret = snmp_config_when(line, NORMAL_CONFIG);
    }
    return ret;
}
