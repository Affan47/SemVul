svc (void)
{
#if !defined (ACE_WIN32)

  sigset_t RT_signals;

  sigemptyset (&RT_signals);
  for (int si = ACE_SIGRTMIN; si <= ACE_SIGRTMAX; si++)
    sigaddset (&RT_signals, si);

  if (ACE_OS::pthread_sigmask (SIG_BLOCK, &RT_signals, 0) != 0)
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("Error:(%P | %t):%p\n"),
                ACE_TEXT ("pthread_sigmask")));
#endif

  reactor_.owner (ACE_Thread::self ());
  reactor_.run_reactor_event_loop ();

  return 0;
}
