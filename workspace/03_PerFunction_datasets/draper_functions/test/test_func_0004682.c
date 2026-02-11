restore_default_signal (sig)
     int sig;
{
  if (SPECIAL_TRAP (sig))
    {
      if ((sig != DEBUG_TRAP && sig != ERROR_TRAP && sig != RETURN_TRAP) ||
	  (sigmodes[sig] & SIG_INPROGRESS) == 0)
	free_trap_command (sig);
      trap_list[sig] = (char *)NULL;
      sigmodes[sig] &= ~SIG_TRAPPED;
      if (sigmodes[sig] & SIG_INPROGRESS)
	sigmodes[sig] |= SIG_CHANGED;
      return;
    }

  GET_ORIGINAL_SIGNAL (sig);


  if (sigmodes[sig] & SIG_HARD_IGNORE)
    return;


  if ((sigmodes[sig] & SIG_TRAPPED) == 0)
    return;


  if ((sigmodes[sig] & SIG_NO_TRAP) == 0)
    set_signal_handler (sig, original_signals[sig]);


  change_signal (sig, (char *)DEFAULT_SIG);


  sigmodes[sig] &= ~SIG_TRAPPED;
}
