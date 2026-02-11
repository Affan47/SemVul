wait_for_proc (boolean all, unsigned int minreap)
{
  unsigned int reaped = 0;

  while (procs_executing)
    {
      unsigned int i;
      int status;
      pid_t pid;
      int wflags = 0;

      if (!all)
	{
	  if (reaped >= minreap)
	    {


	      wflags = WNOHANG;
	    }
	}

      do
	{


	  while ((pid = waitpid (-1, &status, wflags)) == (pid_t) -1)
	    {
	      if (errno != EINTR)
		error (1, errno, _("error waiting for child process"));
	    }


	  if (pid)
	    {
	      for (i = 0; i < pids_alloc && pid != pids[i]; i++)
		;
	    }
	}
      while (pid && i == pids_alloc);

      if (!pid)
	{
	  if (!(wflags & WNOHANG))
	    {


	      error (0, 0, _("Warning: Lost track of %d child processes"),
		     procs_executing);
	    }
	  else
	    {


	    }
	  break;
	}


      pids[i] = 0;
      procs_executing--;
      reaped++;

      if (WEXITSTATUS (status) == 126 || WEXITSTATUS (status) == 127)
	exit (WEXITSTATUS (status));
      if (WEXITSTATUS (status) == 255)
	error (124, 0, _("%s: exited with status 255; aborting"), bc_state.cmd_argv[0]);
      if (WIFSTOPPED (status))
	error (125, 0, _("%s: stopped by signal %d"), bc_state.cmd_argv[0], WSTOPSIG (status));
      if (WIFSIGNALED (status))
	error (125, 0, _("%s: terminated by signal %d"), bc_state.cmd_argv[0], WTERMSIG (status));
      if (WEXITSTATUS (status) != 0)
	child_error = 123;
    }
}
