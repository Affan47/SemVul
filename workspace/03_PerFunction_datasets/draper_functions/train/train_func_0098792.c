rl_complete (ignore, invoking_key)
     int ignore, invoking_key;
{
  if (rl_inhibit_completion)
    return (_rl_insert_char (ignore, invoking_key));
  else if (rl_last_func == rl_complete && !completion_changed_buffer)
    return (rl_complete_internal ('?'));
  else if (_rl_complete_show_all)
    return (rl_complete_internal ('!'));
  else if (_rl_complete_show_unmodified)
    return (rl_complete_internal ('@'));
  else
    return (rl_complete_internal (TAB));
}
