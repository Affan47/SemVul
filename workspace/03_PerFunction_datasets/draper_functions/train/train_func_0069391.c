procmgr_send_spawn_cmd(fcgid_command * command,
                                    request_rec * r)
{
    apr_status_t rv;
    char notifybyte;
    apr_size_t nbytes = sizeof(*command);


    if ((rv = apr_global_mutex_lock(g_pipelock)) != APR_SUCCESS) {
        ap_log_rerror(APLOG_MARK, APLOG_EMERG, rv, r,
                      "mod_fcgid: can't get pipe mutex");
        exit(0);
    }

    if ((rv =
         apr_file_write_full(g_ap_write_pipe, command, nbytes,
                             NULL)) != APR_SUCCESS) {

        ap_log_rerror(APLOG_MARK, APLOG_WARNING, rv, r,
                      "mod_fcgid: can't write spawn command");
    } else {

        nbytes = sizeof(notifybyte);
        if ((rv =
             apr_file_read(g_ap_read_pipe, &notifybyte,
                           &nbytes)) != APR_SUCCESS) {
            ap_log_rerror(APLOG_MARK, APLOG_WARNING, rv, r,
                          "mod_fcgid: can't get notify from process manager");
        }
    }


    if ((rv = apr_global_mutex_unlock(g_pipelock)) != APR_SUCCESS) {
        ap_log_rerror(APLOG_MARK, APLOG_EMERG, rv, r,
                      "mod_fcgid: can't release pipe mutex");
        exit(0);
    }

    return APR_SUCCESS;
}
