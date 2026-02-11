initialize_shell_signals ()
{
  if (interactive)
    initialize_terminating_signals ();

#if defined (JOB_CONTROL) || defined (HAVE_POSIX_SIGNALS)


  sigemptyset (&top_level_mask);
  sigprocmask (SIG_BLOCK, (sigset_t *)NULL, &top_level_mask);
#  if defined (SIGCHLD)
  sigdelset (&top_level_mask, SIGCHLD);
#  endif
#endif


  set_signal_handler (SIGQUIT, SIG_IGN);

  if (interactive)
    {
      set_signal_handler (SIGINT, sigint_sighandler);
      set_signal_handler (SIGTERM, SIG_IGN);
      set_sigwinch_handler ();
    }
}
