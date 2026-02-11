_snmpNotifyFilterTable_container_save_rows(int majorID, int minorID,
                                           void *serverarg,
                                           void *clientarg)
{
    char            sep[] =
        "##############################################################";
    char            buf[] =
        "#\n" "# snmpNotifyFilterTable persistent data\n" "#";
    char           *type = netsnmp_ds_get_string(NETSNMP_DS_LIBRARY_ID,
                                                 NETSNMP_DS_LIB_APPTYPE);
    netsnmp_container *c = *(netsnmp_container **)clientarg;

    DEBUGMSGTL(("internal:snmpNotifyFilterTable:"
                "_snmpNotifyFilterTable_container_save_rows",
                "saving %" NETSNMP_PRIz "u rows\n", CONTAINER_SIZE(c)));

    read_config_store((char *) type, sep);
    read_config_store((char *) type, buf);


    CONTAINER_FOR_EACH(c, (netsnmp_container_obj_func *)
                       _snmpNotifyFilterTable_container_row_save, type);

    read_config_store((char *) type, sep);
    read_config_store((char *) type, "\n");


    return SNMPERR_SUCCESS;
}
