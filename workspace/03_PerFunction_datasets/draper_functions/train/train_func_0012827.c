netsnmp_check_requests_status(netsnmp_agent_session *asp,
                              netsnmp_request_info *requests,
                              int look_for_specific)
{


    while (requests) {
        if(requests->agent_req_info != asp->reqinfo) {
            DEBUGMSGTL(("verbose:asp",
                        "**reqinfo %p doesn't match cached reqinfo %p\n",
                        asp->reqinfo, requests->agent_req_info));
        }
        if (requests->status != SNMP_ERR_NOERROR &&
            (!look_for_specific || requests->status == look_for_specific)
            && (look_for_specific || asp->index == 0
                || requests->index < asp->index)) {
            asp->index = requests->index;
            asp->status = requests->status;
        }
        requests = requests->next;
    }
    return asp->status;
}
