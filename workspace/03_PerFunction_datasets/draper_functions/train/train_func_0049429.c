process_signal(int sig) {
  __daemon_run = 0;
  if (sig == SIGHUP) {
    LOG(LOG_INFO, INFO_DAEMON_RELOAD);
    __hup = 1;
  } else {
    LOG(LOG_WARNING, ERR_DAEMON_TERMINATE, sig);
    __hup = 0;
  }

  return;
}
