sigar_ptql_query_find_process(sigar_t *sigar,
                                                 sigar_ptql_query_t *query,
                                                 sigar_pid_t *pid)
{
    int status;
    int i, matches=0;
    sigar_proc_list_t *pids;

    status = ptql_proc_list_get(sigar, query, &pids);
    if (status != SIGAR_OK) {
        return status;
    }

    for (i=0; i<pids->number; i++) {
        int query_status =
            sigar_ptql_query_match(sigar, query, pids->data[i]);

        if (query_status == SIGAR_OK) {
            *pid = pids->data[i];
            matches++;
        }
        else if (query_status == SIGAR_ENOTIMPL) {

            status = query_status;
            break;
        }
    }

    ptql_proc_list_destroy(sigar, pids);

    if (status != SIGAR_OK) {
        return status;
    }

    if (matches == 1) {
        return SIGAR_OK;
    }
    else if (matches == 0) {
        sigar_strerror_set(sigar,
                           "Query did not match any processes");
    }
    else {
        sigar_strerror_printf(sigar,
                              "Query matched multiple processes (%d)",
                              matches);
    }

    return -1;
}
