remove_history (which)
     int which;
{
  HIST_ENTRY *return_value;
  register int i;

  if (which < 0 || which >= history_length || history_length ==  0 || the_history == 0)
    return ((HIST_ENTRY *)NULL);

  return_value = the_history[which];

  for (i = which; i < history_length; i++)
    the_history[i] = the_history[i + 1];

  history_length--;

  return (return_value);
}
