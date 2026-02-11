netsnmp_request_set_error_all( netsnmp_request_info *requests, int error)
{
    int mode, rc, result = SNMPERR_SUCCESS;

    if((NULL == requests) || (NULL == requests->agent_req_info))
        return SNMPERR_NO_VARS;

    mode = requests->agent_req_info->mode;

    for(; requests ; requests = requests->next) {


        netsnmp_assert(NULL != requests->agent_req_info);
        netsnmp_assert(mode == requests->agent_req_info->mode);


        if((rc = _request_set_error(requests, mode, error))) {
            snmp_log(LOG_WARNING,"got %d while setting request error\n", rc);
            result = rc;
        }
    }
    return result;
}
