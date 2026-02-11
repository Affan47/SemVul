set_signal (sig, string)
     int sig;
     char *string;
{
  if (SPECIAL_TRAP (sig))
    {
      change_signal (sig, savestring (string));
      if (sig == EXIT_TRAP && interactive == 0)
	initialize_terminating_signals ();
      return;
    }


  if (sigmodes[sig] & SIG_HARD_IGNORE)
    return;


  if ((sigmodes[sig] & SIG_TRAPPED) == 0)
    {

      if (original_signals[sig] == IMPOSSIBLE_TRAP_HANDLER)
        GETORIGSIG (sig);
      if (original_signals[sig] == SIG_IGN)
	return;
    }


  if ((sigmodes[sig] & SIG_NO_TRAP) == 0)
    {
      set_signal_handler (sig, SIG_IGN);
      change_signal (sig, savestring (string));
      set_signal_handler (sig, trap_handler);
    }
  else
    change_signal (sig, savestring (string));
}
