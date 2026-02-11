rl_end_kbd_macro (count, ignore)
     int count, ignore;
{
  if (RL_ISSTATE (RL_STATE_MACRODEF) == 0)
    {
      _rl_abort_internal ();
      return -1;
    }

  current_macro_index -= rl_key_sequence_length - 1;
  current_macro[current_macro_index] = '\0';

  RL_UNSETSTATE(RL_STATE_MACRODEF);

  return (rl_call_last_kbd_macro (--count, 0));
}
