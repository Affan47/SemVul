sigchld_callback(struct Event *ev)
{
  pid_t cpid;
  int status;

  ++SignalCounter.chld;
  do {
    cpid = waitpid(-1, &status, WNOHANG);
    if (cpid > 0)
      do_unregister_child(cpid, 1, status);
  } while (cpid > 0);
}
