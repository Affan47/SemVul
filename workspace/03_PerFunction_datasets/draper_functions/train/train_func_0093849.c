initialize_job_control (force)
     int force;
{
  pid_t t;
  int t_errno;

  t_errno = -1;
  shell_pgrp = getpgid (0);

  if (shell_pgrp == -1)
    {
      sys_error (_("initialize_job_control: getpgrp failed"));
      exit (1);
    }


  if (interactive == 0)
    {
      job_control = 0;
      original_pgrp = NO_PID;
      shell_tty = fileno (stderr);
    }
  else
    {
      shell_tty = -1;


      if (forced_interactive && isatty (fileno (stderr)) == 0)
	shell_tty = open ("/dev/tty", O_RDWR|O_NONBLOCK);


      if (shell_tty == -1)
	shell_tty = dup (fileno (stderr));

      shell_tty = move_to_high_fd (shell_tty, 1, -1);


      if (shell_pgrp == 0)
	{
	  shell_pgrp = getpid ();
	  setpgid (0, shell_pgrp);
	  tcsetpgrp (shell_tty, shell_pgrp);
	}

      while ((terminal_pgrp = tcgetpgrp (shell_tty)) != -1)
	{
	  if (shell_pgrp != terminal_pgrp)
	    {
	      SigHandler *ottin;

	      ottin = set_signal_handler(SIGTTIN, SIG_DFL);
	      kill (0, SIGTTIN);
	      set_signal_handler (SIGTTIN, ottin);
	      continue;
	    }
	  break;
	}

      if (terminal_pgrp == -1)
	t_errno = errno;


      if (set_new_line_discipline (shell_tty) < 0)
	{
	  sys_error (_("initialize_job_control: line discipline"));
	  job_control = 0;
	}
      else
	{
	  original_pgrp = shell_pgrp;
	  shell_pgrp = getpid ();

	  if ((original_pgrp != shell_pgrp) && (setpgid (0, shell_pgrp) < 0))
	    {
	      sys_error (_("initialize_job_control: setpgid"));
	      shell_pgrp = original_pgrp;
	    }

	  job_control = 1;


	  if (shell_pgrp != original_pgrp && shell_pgrp != terminal_pgrp)
	    {
	      if (give_terminal_to (shell_pgrp, 0) < 0)
		{
		  t_errno = errno;
		  setpgid (0, original_pgrp);
		  shell_pgrp = original_pgrp;
		  job_control = 0;
		}
	    }

	  if (job_control && ((t = tcgetpgrp (shell_tty)) == -1 || t != shell_pgrp))
	    {
	      if (t_errno != -1)
		errno = t_errno;
	      sys_error (_("cannot set terminal process group (%d)"), t);
	      job_control = 0;
	    }
	}
      if (job_control == 0)
	internal_error (_("no job control in this shell"));
    }

  if (shell_tty != fileno (stderr))
    SET_CLOSE_ON_EXEC (shell_tty);

  set_signal_handler (SIGCHLD, sigchld_handler);

  change_flag ('m', job_control ? '-' : '+');

  if (interactive)
    get_tty_state ();

  if (js.c_childmax < 0)
    js.c_childmax = getmaxchild ();
  if (js.c_childmax < 0)
    js.c_childmax = DEFAULT_CHILD_MAX;

  return job_control;
}
