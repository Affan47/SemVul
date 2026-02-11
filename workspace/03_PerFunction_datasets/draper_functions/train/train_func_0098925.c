rl_echo_signal_char (sig)
     int sig;
{
  char cstr[3];
  int cslen, c;

  if (_rl_echoctl == 0 || _rl_echo_control_chars == 0)
    return;

  switch (sig)
    {
    case SIGINT:  c = _rl_intr_char; break;
#if defined (SIGQUIT)
    case SIGQUIT: c = _rl_quit_char; break;
#endif
#if defined (SIGTSTP)
    case SIGTSTP: c = _rl_susp_char; break;
#endif
    default: return;
    }

  if (CTRL_CHAR (c) || c == RUBOUT)
    {
      cstr[0] = '^';
      cstr[1] = CTRL_CHAR (c) ? UNCTRL (c) : '?';
      cstr[cslen = 2] = '\0';
    }
  else
    {
      cstr[0] = c;
      cstr[cslen = 1] = '\0';
    }

  _rl_output_some_chars (cstr, cslen);
}
