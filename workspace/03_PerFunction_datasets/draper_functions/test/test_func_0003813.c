sigchld(int sig attribute((unused)))
{
  const int old_errno = errno;
  int status;
  pid_t pid;

  while ((pid = waitpid(-1, &status, WNOHANG|WUNTRACED)) != 0)
    {
      int s;

      if (errno == ECHILD)
	break;

      if (pid < 0)
	continue;

      if (pid == splashpid)
	{
	  splashpid = (pid_t)0;
	  continue;
	}

      for (s = 0; s < par; s++)
	{
	  struct prg * p = prgs + s;
	  if (p == interactive_task)
	    continue;
	  if (p->pid != pid)
	    continue;
	  if (p->flags & PRUNNING)
	    {
	      p->status = status;
	      p->flags |= PFINISHED;
	      break;
	    }
	}
    }

  signaled = 1;
  errno = old_errno;
}
