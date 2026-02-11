table_helper_cleanup(netsnmp_agent_request_info *reqinfo,
                     netsnmp_request_info *request, int status)
{
    netsnmp_set_request_error(reqinfo, request, status);
    netsnmp_free_request_data_sets(request);
    if (!request)
        return;
    request->parent_data = NULL;
}
