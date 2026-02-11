handle_ipDefaultTTL(netsnmp_mib_handler *handler,
                    netsnmp_handler_registration *reginfo,
                    netsnmp_agent_request_info   *reqinfo,
                    netsnmp_request_info         *requests)
{
    int      rc;
    u_long   value;


    switch(reqinfo->mode) {

        case MODE_GET:
            rc = netsnmp_arch_ip_scalars_ipDefaultTTL_get(&value);
            if (rc != 0) {
                netsnmp_set_request_error(reqinfo, requests,
                                      SNMP_NOSUCHINSTANCE);
            }
            else {
                snmp_set_var_typed_value(requests->requestvb, ASN_INTEGER,
                                     (u_char *)&value, sizeof(value));
            }
            break;

#ifndef NETSNMP_NO_WRITE_SUPPORT


        case MODE_SET_RESERVE1:
            break;

        case MODE_SET_RESERVE2:


            rc = netsnmp_arch_ip_scalars_ipDefaultTTL_get(&value);
            if (rc < 0) {
                netsnmp_set_request_error(reqinfo, requests,
                                          SNMP_ERR_NOCREATION);
            } else {
                u_long *value_save;
                memdup((u_char **) & value_save, (u_char *) &value,
                       sizeof(value));
                if ( NULL == value_save )
                    netsnmp_set_request_error(reqinfo, requests, SNMP_ERR_RESOURCEUNAVAILABLE);
                else
                    netsnmp_request_add_list_data(requests,
                                                  netsnmp_create_data_list
                                                  ("ipttl", value_save,
                                                  free));
	    }
            break;

        case MODE_SET_FREE:


            break;

        case MODE_SET_ACTION:

            value =  *(requests->requestvb->val.integer);
            rc = netsnmp_arch_ip_scalars_ipDefaultTTL_set(value);
            if ( 0 != rc ) {
                netsnmp_set_request_error(reqinfo, requests, rc);
            }
            break;

        case MODE_SET_COMMIT:
            break;

        case MODE_SET_UNDO:
             value =
                 *((u_long *) netsnmp_request_get_list_data(requests,
                                                            "ipttl"));
             rc = netsnmp_arch_ip_scalars_ipDefaultTTL_set(value);
             if ( 0 != rc ) {
                 netsnmp_set_request_error(reqinfo, requests, SNMP_ERR_UNDOFAILED);
             }
             break;
#endif

        default:

            snmp_log(LOG_ERR, "unknown mode (%d) in handle_ipDefaultTTL\n", reqinfo->mode );
            return SNMP_ERR_GENERR;
    }

    return SNMP_ERR_NOERROR;
}
