init_proc(void)
{


    struct variable2 extensible_proc_variables[] = {
        {MIBINDEX, ASN_INTEGER, NETSNMP_OLDAPI_RONLY,
         var_extensible_proc, 1, {MIBINDEX}},
        {ERRORNAME, ASN_OCTET_STR, NETSNMP_OLDAPI_RONLY,
         var_extensible_proc, 1, {ERRORNAME}},
        {PROCMIN, ASN_INTEGER, NETSNMP_OLDAPI_RONLY,
         var_extensible_proc, 1, {PROCMIN}},
        {PROCMAX, ASN_INTEGER, NETSNMP_OLDAPI_RONLY,
         var_extensible_proc, 1, {PROCMAX}},
        {PROCCOUNT, ASN_INTEGER, NETSNMP_OLDAPI_RONLY,
         var_extensible_proc, 1, {PROCCOUNT}},
        {ERRORFLAG, ASN_INTEGER, NETSNMP_OLDAPI_RONLY,
         var_extensible_proc, 1, {ERRORFLAG}},
        {ERRORMSG, ASN_OCTET_STR, NETSNMP_OLDAPI_RONLY,
         var_extensible_proc, 1, {ERRORMSG}},
        {ERRORFIX, ASN_INTEGER, NETSNMP_OLDAPI_RWRITE,
         var_extensible_proc, 1, {ERRORFIX}},
        {ERRORFIXCMD, ASN_OCTET_STR, NETSNMP_OLDAPI_RONLY,
         var_extensible_proc, 1, {ERRORFIXCMD}}
    };


    oid             proc_variables_oid[] = { NETSNMP_UCDAVIS_MIB, NETSNMP_PROCMIBNUM, 1 };


    REGISTER_MIB("ucd-snmp/proc", extensible_proc_variables, variable2,
                 proc_variables_oid);

    snmpd_register_config_handler("proc", proc_parse_config,
                                  proc_free_config,
                                  "process-name [max-num] [min-num]");
    snmpd_register_config_handler("procfix", procfix_parse_config, NULL,
                                  "process-name program [arguments...]");
}
