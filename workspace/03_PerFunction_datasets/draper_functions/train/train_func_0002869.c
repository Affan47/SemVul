signal_pipe_dispatch(void) {
    int sig, err;

    s_log(LOG_DEBUG, "Dispatching signals from the signal pipe");
    while(readsocket(signal_pipe[0], (char *)&sig, sizeof sig)==sizeof sig) {
        switch(sig) {
#ifndef USE_WIN32
        case SIGCHLD:
            s_log(LOG_DEBUG, "Processing SIGCHLD");
#ifdef USE_FORK
            client_status();
#else
            child_status();
#endif
            break;
#endif
        case SIGNAL_RELOAD_CONFIG:
            s_log(LOG_DEBUG, "Processing SIGNAL_RELOAD_CONFIG");
            err=parse_conf(CONF_RELOAD);
            if(err) {
                s_log(LOG_ERR, "Failed to reload the configuration file");
            } else {
                unbind_ports();
                log_close();
                apply_conf();
                log_open();
                if(bind_ports()) {

                }
            }
            break;
        case SIGNAL_REOPEN_LOG:
            s_log(LOG_DEBUG, "Processing SIGNAL_REOPEN_LOG");
            log_close();
            log_open();
            s_log(LOG_NOTICE, "Log file reopened");
            break;
        case SIGNAL_TERMINATE:
            s_log(LOG_DEBUG, "Processing SIGNAL_TERMINATE");
            s_log(LOG_NOTICE, "Terminated");
            return 2;
        default:
            s_log(LOG_ERR, "Received signal %d; terminating", sig);
            return 1;
        }
    }
    s_log(LOG_DEBUG, "Signal pipe is empty");
    return 0;
}
