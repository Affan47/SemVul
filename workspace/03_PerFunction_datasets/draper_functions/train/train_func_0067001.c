handle_mteResourceGroup(netsnmp_mib_handler          *handler,
                        netsnmp_handler_registration *reginfo,
                        netsnmp_agent_request_info   *reqinfo,
                        netsnmp_request_info         *requests)
{
    oid  obj;
    long value = 0;

    switch (reqinfo->mode) {
    case MODE_GET:
        obj = requests->requestvb->name[ requests->requestvb->name_length-2 ];
        switch (obj) {
	case MTE_RESOURCE_SAMPLE_MINFREQ:
             value = 1;
             snmp_set_var_typed_value(requests->requestvb, ASN_INTEGER,
                                      (u_char *)&value, sizeof(value));
             break;

	case MTE_RESOURCE_SAMPLE_MAX_INST:
             value = 0;
             snmp_set_var_typed_value(requests->requestvb, ASN_UNSIGNED,
                                      (u_char *)&value, sizeof(value));
             break;

	case MTE_RESOURCE_SAMPLE_INSTANCES:
#ifdef USING_DISMAN_EVENT_MTETRIGGER_MODULE
             value = mteTrigger_getNumEntries(0);
#else
             value = 0;
#endif
             snmp_set_var_typed_value(requests->requestvb, ASN_GAUGE,
                                      (u_char *)&value, sizeof(value));
             break;

	case MTE_RESOURCE_SAMPLE_HIGH:
#ifdef USING_DISMAN_EVENT_MTETRIGGER_MODULE
             value = mteTrigger_getNumEntries(1);
#else
             value = 0;
#endif
             snmp_set_var_typed_value(requests->requestvb, ASN_GAUGE,
                                      (u_char *)&value, sizeof(value));
             break;

	case MTE_RESOURCE_SAMPLE_LACKS:
             value = 0;
             snmp_set_var_typed_value(requests->requestvb, ASN_COUNTER,
                                      (u_char *)&value, sizeof(value));
             break;

        default:
             snmp_log(LOG_ERR,
                 "unknown object (%d) in handle_mteResourceGroup\n", (int)obj);
             return SNMP_ERR_GENERR;
        }
        break;

    default:


        snmp_log(LOG_ERR,
                 "unknown mode (%d) in handle_mteResourceGroup\n",
                 reqinfo->mode);
        return SNMP_ERR_GENERR;
    }

    return SNMP_ERR_NOERROR;
}
