reopen_all() {
  if (freopen("/dev/null", "r", stdin) == NULL ||
      freopen("/dev/null", "w", stdout) == NULL ||
      freopen("/dev/null", "w", stdout) == NULL)
    fatal("freopen: %s", strerror(errno));
}
