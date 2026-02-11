spawn(const char *cmd)
{
  extern char *x_server;
#ifdef HAVE_ALLOCA
  char *line=alloca(strlen(x_server)+strlen(cmd)+28);
#else
  char *line=malloc(strlen(x_server)+strlen(cmd)+28);
  if(line) {
#endif
  char *dot;
  sprintf(line, "DISPLAY='%s", x_server);
  if(!(dot=strrchr(line, '.')) || strchr(dot, ':'))
    dot=line+strlen(line);
  sprintf(dot, ".%d' %s &", scr->number, cmd);
#ifdef __ultrix
  {
    int pid, status;
    if ((pid = fork ()) == 0) {
      (void) setsid();
      execl ("/bin/sh", "sh", "-c", line, 0);
    } else
      waitpid (pid, &status, 0);
  }
#else
  system(line);
#endif
#ifndef HAVE_ALLOCA
    free(line);
  }
#endif
}
