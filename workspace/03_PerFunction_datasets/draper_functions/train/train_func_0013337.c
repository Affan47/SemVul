__assuan_waitpid (assuan_context_t ctx, pid_t pid, int nowait,
		  int *status, int options)
{


  if (! nowait)
    return waitpid (pid, NULL, 0);
  return 0;
}
