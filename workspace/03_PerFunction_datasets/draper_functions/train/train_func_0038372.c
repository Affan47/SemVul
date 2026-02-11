set_signal(int signo, void (*handler)(int)))(int)
{
  struct sigaction sa, osa;

  memset(&sa, 0, sizeof sa);
  sa.sa_handler = handler;
  sigemptyset(&sa.sa_mask);
  sa.sa_flags = signo != SIGALRM ? SA_RESTART
#ifdef HAVE_SA_INTERRUPT
    : SA_INTERRUPT;
#else
    : 0;
#endif
  return sigaction(signo, &sa, &osa) ? SIG_ERR : osa.sa_handler;
}
