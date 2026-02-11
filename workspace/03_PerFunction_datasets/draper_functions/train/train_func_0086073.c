dmn_signal(const char* pidfile, int sig) {
    dmn_assert(pidfile);

    int rv = 1;
    const pid_t pid = check_pidfile(pidfile);
    if(!pid) {
        dmn_log_err("Did not find a running daemon to signal!");
    }
    else if(kill(pid, sig)) {
        dmn_log_err("Cannot signal daemon at pid %li", (long)pid);
    }
    else {
        dmn_log_info("SIGHUP sent to daemon instance at pid %li", (long)pid);
        rv = 0;
    }

    return rv;
}
