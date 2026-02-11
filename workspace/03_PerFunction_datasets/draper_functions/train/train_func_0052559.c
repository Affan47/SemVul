install_watchdog(const char *toolName, const char *outFileName) {
  wToolname=toolName;
  wOutname=outFileName;

  if(startTime<0) {
    startTime = uprv_getRawUTCtime();
  }
  signal(SIGALRM, &alarm_fn);

  alarm(firstSeconds);
}
