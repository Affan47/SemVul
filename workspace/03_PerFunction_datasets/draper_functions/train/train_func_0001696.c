fork2() {
  pid_t pid;
  int status;

  sigset_t set,oset;
  sigfillset(& set);
  xprintf (">>>>>>>>Forking<<<<<<<<,\n");
  sigprocmask(SIG_SETMASK,&set,&oset);

  if (!(pid = fork())) {
    xprintf ("child\n");
    switch (fork()) {
    case 0:
      xprintf ("child 2\n");
      sigprocmask(SIG_SETMASK,&oset,&set);
      return 0;
    case -1:
      xprintf ("fork 2 failed!\n");
      _exit(errno);
    default:
      xprintf ("parent 2\n");
      _exit(0);
    }
  }

  xprintf ("parent, child pid =%d\n", pid);

  if (pid < 0 || waitpid(pid,&status,0) < 0) {
      xprintf ("waitpid failed! (pid==%d)\n", pid);
    sigprocmask(SIG_SETMASK,&oset,&set);
    return -1;
  }
  sigprocmask(SIG_SETMASK,&oset,&set);

  xprintf ("waitpid done\n");

  if (WIFEXITED(status))
    if (WEXITSTATUS(status) == 0) {
      xprintf ("fork 2 succeeded\n");
      return 1;
    } else
      errno = WEXITSTATUS(status);
  else
    errno = EINTR;

  xprintf ("parent done\n");

  return -1;
}
