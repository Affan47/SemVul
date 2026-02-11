operate_and_get_next (count, c)
     int count, c;
{
  int where;


  rl_newline (1, c);


  where = where_history ();

  if ((history_is_stifled () && (history_length >= history_max_entries)) ||
      (where >= history_length - 1))
    saved_history_line_to_use = where;
  else
    saved_history_line_to_use = where + 1;

  old_rl_startup_hook = rl_startup_hook;
  rl_startup_hook = set_saved_history;

  return 0;
}
