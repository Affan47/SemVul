install_signal_handlers(void)
{

  struct sigaction action;
  memset(&action, 0, sizeof(action));
  action.sa_handler = receive_signal;

  if(sigaction(SIGUSR1, &action, NULL) == -1)
  {
    perror("sigaction() failed");
    return -1;
  }

  return 0;
}
