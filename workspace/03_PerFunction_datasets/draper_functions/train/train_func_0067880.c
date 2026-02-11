runpoll(int msecs) {
  int ret;
  while (1) {
	  ret = poll(items, nitems, (msecs >= 1000) ? 1000 : msecs);
	  if (ret < 0 && errno != EINTR) {
      throw PException(true, "Error during poll: %d->%d", ret, errno);
    }
    if (ret > 0) return;
    if (posclient_quitflag) return;
    if (msecs <= 1000) return;
    msecs -= 1000;

  }
}
