uv__signal_register_handler(int signum) {

  struct sigaction sa;


  memset(&sa, 0, sizeof(sa));
  if (sigfillset(&sa.sa_mask))
    abort();
  sa.sa_handler = uv__signal_handler;


  if (sigaction(signum, &sa, NULL))
    return -errno;

  return 0;
}
