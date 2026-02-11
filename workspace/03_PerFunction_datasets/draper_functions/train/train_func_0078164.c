rl_vi_fetch_history (count, c)
     int count, c;
{
  int wanted;


  if (rl_explicit_arg)
    {
      wanted = history_base + where_history () - count;
      if (wanted <= 0)
        rl_beginning_of_history (0, 0);
      else
        rl_get_previous_history (wanted, c);
    }
  else
    rl_beginning_of_history (count, 0);
  return (0);
}
