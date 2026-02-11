est_signal(int signum, void (*sighandler)(int)){
#if defined(_SYS_MSVC_) || defined(_SYS_MINGW_)
  static int first = TRUE;
  int i;
  assert(signum >= 0 && sighandler);
  if(first){
    for(i = 1; i < ESTSIGNUM; i++){
      est_signal_handlers[i] = NULL;
    }
    SetConsoleCtrlHandler((PHANDLER_ROUTINE)est_signal_dispatch, TRUE);
    first = FALSE;
  }
  if(signum >= ESTSIGNUM) return;
  if(sighandler == SIG_IGN){
    signal(signum, SIG_IGN);
  } else if(sighandler == SIG_DFL){
    signal(signum, SIG_DFL);
  } else {
    signal(signum, (void (*)(int))est_signal_dispatch);
    est_signal_handlers[signum] = sighandler;
  }
#else
  static int first = TRUE;
  struct sigaction act;
  int i;
  assert(signum >= 0 && sighandler);
  if(first){
    for(i = 1; i < ESTSIGNUM; i++){
      est_signal_handlers[i] = NULL;
    }
    first = FALSE;
  }
  if(signum >= ESTSIGNUM) return;
  memset(&act, 0, sizeof(act));
  if(sighandler == SIG_IGN){
    act.sa_handler = SIG_IGN;
  } else if(sighandler == SIG_DFL){
    act.sa_handler = SIG_DFL;
  } else {
    act.sa_handler = (void (*)(int))est_signal_dispatch;
    est_signal_handlers[signum] = sighandler;
  }
  sigemptyset(&act.sa_mask);
  act.sa_flags = 0;
  sigaction(signum, &act, NULL);
#endif
}
