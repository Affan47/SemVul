snmpv3_secLevel_conf(const char *word, char *cptr)
{
    int             secLevel;

    if ((secLevel = parse_secLevel_conf( word, cptr )) >= 0 ) {
        netsnmp_ds_set_int(NETSNMP_DS_LIBRARY_ID,
			   NETSNMP_DS_LIB_SECLEVEL, secLevel);
    } else {
	netsnmp_config_error("Unknown security level: %s", cptr);
    }
    DEBUGMSGTL(("snmpv3", "default secLevel set to: %s = %d\n", cptr,
                netsnmp_ds_get_int(NETSNMP_DS_LIBRARY_ID,
				   NETSNMP_DS_LIB_SECLEVEL)));
}
