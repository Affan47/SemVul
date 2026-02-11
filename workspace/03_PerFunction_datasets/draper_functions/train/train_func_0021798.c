check_history_control (line)
     char *line;
{
  HIST_ENTRY *temp;
  int r;

  if (history_control == 0)
    return 1;


  if ((history_control & HC_IGNSPACE) && *line == ' ')
    return 0;


  if (history_control & HC_IGNDUPS)
    {
      using_history ();
      temp = previous_history ();

      r = (temp == 0 || STREQ (temp->line, line) == 0);

      using_history ();

      if (r == 0)
	return r;
    }

  return 1;
}
