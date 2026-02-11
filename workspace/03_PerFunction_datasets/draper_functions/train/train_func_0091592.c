handle_signal(int sig)
{
  message("Got signal %d, child_pid: %d", sig, child_pid);
  terminated= 1;

  if (child_pid > 0)
    kill_child();


  signal(SIGTERM, SIG_IGN);
  signal(SIGINT,  SIG_IGN);


}
