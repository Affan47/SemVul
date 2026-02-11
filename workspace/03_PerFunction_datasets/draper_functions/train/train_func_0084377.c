crashreport(int sig)
{
  struct sigaction sa;
  stack_t          sigstack;


  if (sigaltstack(NULL,&sigstack) < 0)
    return errno;

  if (sigstack.ss_sp == NULL)
  {
    sigstack.ss_sp = malloc(SIGSTKSZ);
    if (sigstack.ss_sp == NULL)
      return errno;

    sigstack.ss_size  = SIGSTKSZ;
    sigstack.ss_flags = 0;

    if (sigaltstack(&sigstack,NULL) < 0)
    {
      int err = errno;
      free(sigstack.ss_sp);
      return err;
    }
  }

  sa.sa_sigaction = crashreport_handler;
  sa.sa_flags     = SA_ONSTACK | SA_SIGINFO | SA_ONESHOT;
  sigemptyset(&sa.sa_mask);

  return sigaction(sig,&sa,NULL);
}
