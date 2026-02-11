handle_memsize(netsnmp_mib_handler *handler,
                netsnmp_handler_registration *reginfo,
                netsnmp_agent_request_info *reqinfo,
                netsnmp_request_info *requests)
{
    netsnmp_memory_info *mem_info;
    int val;


    switch (reqinfo->mode) {
    case MODE_GET:
        netsnmp_memory_load();
        mem_info = netsnmp_memory_get_byIdx( NETSNMP_MEM_TYPE_PHYSMEM, 0 );
        if ( !mem_info || mem_info->size == -1 || mem_info->units == -1 )
            netsnmp_set_request_error( reqinfo, requests, SNMP_NOSUCHOBJECT );
	else {
            val  =  mem_info->size;
            val *= (mem_info->units/1024);
            snmp_set_var_typed_value(requests->requestvb, ASN_INTEGER,
                                     (u_char *)&val, sizeof(val));
        }
        return SNMP_ERR_NOERROR;

    default:


        snmp_log(LOG_ERR, "unknown mode (%d) in handle_memsize\n",
                 reqinfo->mode);
        return SNMP_ERR_GENERR;
    }

    return SNMP_ERR_NOERROR;
}
