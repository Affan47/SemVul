setup_signals(void)
{
    struct sigaction sa;


    sa.sa_handler = signal_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    if (sigaction(SIGTERM, &sa, NULL) < 0) {
        ap_log_error(FCGI_LOG_ALERT, fcgi_apache_main_server,
        "sigaction(SIGTERM) failed");
    }

    if (sigaction(SIGHUP, &sa, NULL) < 0) {
        ap_log_error(FCGI_LOG_ALERT, fcgi_apache_main_server,
        "sigaction(SIGHUP) failed");
    }

    if (sigaction(SIGUSR1, &sa, NULL) < 0) {
        ap_log_error(FCGI_LOG_ALERT, fcgi_apache_main_server,
        "sigaction(SIGUSR1) failed");
    }

    if (sigaction(SIGALRM, &sa, NULL) < 0) {
        ap_log_error(FCGI_LOG_ALERT, fcgi_apache_main_server,
        "sigaction(SIGALRM) failed");
    }
    if (sigaction(SIGCHLD, &sa, NULL) < 0) {
        ap_log_error(FCGI_LOG_ALERT, fcgi_apache_main_server,
        "sigaction(SIGCHLD) failed");
    }
}
