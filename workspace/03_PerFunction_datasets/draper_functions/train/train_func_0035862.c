doprogram(arg)
char *arg;
{
  char *args[5];
  int child;
  int wstat;

  if (!flagdeliver) {
    print("run ");
    printsafe(arg);
    print("\n");
    substdio_flush(subfderr);
    return;
  }

  if (*arg == '!') {
    args[0] = "preline";
    args[1] = "sh";
    args[2] = "-c";
    args[3] = arg + 1;
    args[4] = 0;
  }
  else {
    args[0] = "sh";
    args[1] = "-c";
    args[2] = arg + 1;
    args[3] = 0;
  }

  switch(child = vfork()) {
    case -1:
      strerr_die2sys(111,FATAL,"unable to fork: ");
    case 0:
      sig_pipedefault();
      execvp(*args,args);
      strerr_die4sys(111,FATAL,"unable to run ",arg,": ");
  }

  wait_pid(&wstat,child);
  if (wait_crashed(wstat))
    strerr_die4sys(111,FATAL,"child crashed in ",arg,": ");

  switch(wait_exitcode(wstat)) {
    case 64: case 65: case 70: case 76: case 77: case 78: case 112:
    case 100: _exit(100);
    case 0: break;
    default: _exit(111);
  }

  if (seek_begin(0) == -1)
    strerr_die2sys(111,FATAL,"unable to rewind input: ");
}
