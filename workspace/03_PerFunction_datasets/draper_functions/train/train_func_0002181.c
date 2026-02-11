alarm_timeout (int onoff) {
  static struct sigaction oldaction;

  if (onoff)
    {
      struct sigaction action;

      action.sa_handler = &alarm_handler;
      sigemptyset(&action.sa_mask);
      action.sa_flags = 0;
      sigaction(SIGALRM, &action, &oldaction);

      timeout = 0;
      alarm(2);
    }
  else
    {
      alarm(0);
      sigaction(SIGALRM, &oldaction, NULL);
    }
}
