signal_handler(int sig) {
    switch (sig) {
    case SIGHUP:
        applog(LOG_INFO, "SIGHUP received");
        break;
    case SIGINT:
        applog(LOG_INFO, "SIGINT received, exiting");
        exit(0);
        break;
    case SIGTERM:
        applog(LOG_INFO, "SIGTERM received, exiting");
        exit(0);
        break;
    }
}
