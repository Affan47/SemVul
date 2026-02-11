kwsysProcessesSignalHandler(int signum
#if KWSYSPE_USE_SIGINFO
                                        , siginfo_t* info, void* ucontext
#endif
  )
{
  (void)signum;
#if KWSYSPE_USE_SIGINFO
  (void)info;
  (void)ucontext;
#endif


  {
  int i;
  for(i=0; i < kwsysProcesses.Count; ++i)
    {

    char buf = 1;
    kwsysProcess* cp = kwsysProcesses.Processes[i];
    kwsysProcess_ssize_t status=
      read(cp->PipeReadEnds[KWSYSPE_PIPE_SIGNAL], &buf, 1);
    (void)status;
    status=write(cp->SignalPipe, &buf, 1);
    (void)status;
    }
  }

#if !KWSYSPE_USE_SIGINFO


  {
  struct sigaction newSigChldAction;
  memset(&newSigChldAction, 0, sizeof(struct sigaction));
  newSigChldAction.sa_handler = kwsysProcessesSignalHandler;
  newSigChldAction.sa_flags = SA_NOCLDSTOP;
  while((sigaction(SIGCHLD, &newSigChldAction,
                   &kwsysProcessesOldSigChldAction) < 0) &&
        (errno == EINTR));
  }
#endif
}
