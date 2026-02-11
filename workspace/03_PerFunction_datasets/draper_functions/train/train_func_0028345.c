run_pending_traps ()
{
  register int sig;
  int old_exit_value, *token_state;
  WORD_LIST *save_subst_varlist;

  if (catch_flag == 0)
    return;

  catch_flag = 0;


  old_exit_value = last_command_exit_value;

  for (sig = 1; sig < NSIG; sig++)
    {


      if (pending_traps[sig])
	{
#if defined (HAVE_POSIX_SIGNALS)
	  sigset_t set, oset;

	  sigemptyset (&set);
	  sigemptyset (&oset);

	  sigaddset (&set, sig);
	  sigprocmask (SIG_BLOCK, &set, &oset);
#else
#  if defined (HAVE_BSD_SIGNALS)
	  int oldmask = sigblock (sigmask (sig));
#  endif
#endif

	  if (sig == SIGINT)
	    {
	      run_interrupt_trap ();
	      CLRINTERRUPT;
	    }
#if defined (JOB_CONTROL) && defined (SIGCHLD)
	  else if (sig == SIGCHLD &&
		   trap_list[SIGCHLD] != (char *)IMPOSSIBLE_TRAP_HANDLER &&
		   (sigmodes[SIGCHLD] & SIG_INPROGRESS) == 0)
	    {
	      run_sigchld_trap (pending_traps[sig]);
	    }
#endif
	  else if (trap_list[sig] == (char *)DEFAULT_SIG ||
		   trap_list[sig] == (char *)IGNORE_SIG ||
		   trap_list[sig] == (char *)IMPOSSIBLE_TRAP_HANDLER)
	    {


	      internal_warning (_("run_pending_traps: bad value in trap_list[%d]: %p"),
				sig, trap_list[sig]);
	      if (trap_list[sig] == (char *)DEFAULT_SIG)
		{
		  internal_warning (_("run_pending_traps: signal handler is SIG_DFL, resending %d (%s) to myself"), sig, signal_name (sig));
		  kill (getpid (), sig);
		}
	    }
	  else
	    {
	      token_state = save_token_state ();
	      save_subst_varlist = subst_assign_varlist;
	      subst_assign_varlist = 0;

	      parse_and_execute (savestring (trap_list[sig]), "trap", SEVAL_NONINT|SEVAL_NOHIST|SEVAL_RESETLINE);
	      restore_token_state (token_state);
	      free (token_state);

	      subst_assign_varlist = save_subst_varlist;
	    }

	  pending_traps[sig] = 0;

#if defined (HAVE_POSIX_SIGNALS)
	  sigprocmask (SIG_SETMASK, &oset, (sigset_t *)NULL);
#else
#  if defined (HAVE_BSD_SIGNALS)
	  sigsetmask (oldmask);
#  endif
#endif
	}
    }

  last_command_exit_value = old_exit_value;
}
