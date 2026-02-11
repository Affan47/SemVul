check_pid (char *pidfile)
{
  int pid = read_pid(pidfile);


  if ((!pid) || (pid == getpid ()))
    return 0;


  errno = 0;
  if (kill(pid, 0) && errno == ESRCH)
	  return(0);

  return pid;
}
