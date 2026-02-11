nsTransactionTable_handler(netsnmp_mib_handler *handler,
                           netsnmp_handler_registration *reginfo,
                           netsnmp_agent_request_info *reqinfo,
                           netsnmp_request_info *requests)
{

    netsnmp_table_request_info *table_info;
    netsnmp_variable_list *var;
    netsnmp_agent_session *asp;

    for (; requests; requests = requests->next) {
        var = requests->requestvb;
        if (requests->processed != 0)
            continue;


        asp =
            (netsnmp_agent_session *)
            netsnmp_extract_iterator_context(requests);
        if (asp == NULL) {
            netsnmp_set_request_error(reqinfo, requests,
                                      SNMP_NOSUCHINSTANCE);
        }


        table_info = netsnmp_extract_table_info(requests);


        if (table_info == NULL) {
            continue;
        }

        switch (reqinfo->mode) {


        case MODE_GET:
            switch (table_info->colnum) {

            case COLUMN_NSTRANSACTIONMODE:
                snmp_set_var_typed_value(var, ASN_INTEGER,
                                         (u_char *) & asp->mode,
                                         sizeof(asp->mode));
                break;

            default:


                snmp_log(LOG_ERR,
                         "problem encountered in nsTransactionTable_handler: unknown column\n");
            }
            break;

        default:
            snmp_log(LOG_ERR,
                     "problem encountered in nsTransactionTable_handler: unsupported mode\n");
        }
    }
    return SNMP_ERR_NOERROR;
}
