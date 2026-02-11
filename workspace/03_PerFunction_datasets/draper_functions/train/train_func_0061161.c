wsgi_manage_process(int reason, void *data, apr_wait_t status)
{
    WSGIDaemonProcess *daemon = data;

    switch (reason) {


        case APR_OC_REASON_DEATH: {
            int mpm_state;
            int stopping;


            stopping = 1;

            if (ap_mpm_query(AP_MPMQ_MPM_STATE, &mpm_state) == APR_SUCCESS
                && mpm_state != AP_MPMQ_STOPPING) {
                stopping = 0;
            }

            if (!stopping) {
                ap_log_error(APLOG_MARK, APLOG_INFO, 0,
                             wsgi_server, "mod_wsgi (pid=%d): "
                             "Process '%s' has died, deregister and "
                             "restart it.", daemon->process.pid,
                             daemon->group->name);

                if (WIFEXITED(status)) {
                    ap_log_error(APLOG_MARK, APLOG_INFO, 0,
                             wsgi_server, "mod_wsgi (pid=%d): "
                             "Process '%s' terminated normally, exit code %d",
                             daemon->process.pid, daemon->group->name,
                             WEXITSTATUS(status));
                }
                else if (WIFSIGNALED(status)) {
                    ap_log_error(APLOG_MARK, APLOG_INFO, 0,
                             wsgi_server, "mod_wsgi (pid=%d): "
                             "Process '%s' terminated by signal %d",
                             daemon->process.pid, daemon->group->name,
                             WTERMSIG(status));
                }
            }
            else {
                ap_log_error(APLOG_MARK, APLOG_INFO, 0,
                             wsgi_server, "mod_wsgi (pid=%d): "
                             "Process '%s' has died but server is "
                             "being stopped, deregister it.",
                             daemon->process.pid, daemon->group->name);
            }


            apr_proc_other_child_unregister(daemon);


            if (!stopping)
                wsgi_start_process(wsgi_parent_pool, daemon);

            break;
        }


        case APR_OC_REASON_RESTART: {

            ap_log_error(APLOG_MARK, APLOG_INFO, 0,
                         wsgi_server, "mod_wsgi (pid=%d): "
                         "Process '%s' to be deregistered, as server is "
                         "restarting or being shutdown.",
                         daemon->process.pid, daemon->group->name);


            apr_proc_other_child_unregister(daemon);

            break;
        }


        case APR_OC_REASON_LOST: {

            ap_log_error(APLOG_MARK, APLOG_INFO, 0,
                         wsgi_server, "mod_wsgi (pid=%d): "
                         "Process '%s' appears to have been lost, "
                         "deregister and restart it.",
                         daemon->process.pid, daemon->group->name);


            apr_proc_other_child_unregister(daemon);


            wsgi_start_process(wsgi_parent_pool, daemon);

            break;
        }


        case APR_OC_REASON_UNREGISTER: {


            ap_log_error(APLOG_MARK, APLOG_INFO, 0,
                         wsgi_server, "mod_wsgi (pid=%d): "
                         "Process '%s' has been deregistered and will "
                         "no longer be monitored.", daemon->process.pid,
                         daemon->group->name);

            break;
        }

        default: {
            ap_log_error(APLOG_MARK, APLOG_INFO, 0,
                         wsgi_server, "mod_wsgi (pid=%d): "
                         "Process '%s' targeted by unexpected event %d.",
                         daemon->process.pid, daemon->group->name, reason);
        }
    }
}
