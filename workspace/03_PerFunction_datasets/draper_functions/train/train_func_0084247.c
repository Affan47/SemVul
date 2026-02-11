set_daemon(void) {
    settings.daemonmode = 1;
    if (settings.logfilename[0] == '\0') {
        settings.logfilename = default_daemon_log;
    }
}
