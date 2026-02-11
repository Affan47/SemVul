_rl_overwrite_rubout (count, key)
     int count, key;
{
  int opoint;
  int i, l;

  if (rl_point == 0)
    {
      rl_ding ();
      return 1;
    }

  opoint = rl_point;


  for (i = l = 0; i < count; i++)
    {
      rl_backward_char (1, key);
      l += rl_character_len (rl_line_buffer[rl_point], rl_point);
    }

  rl_begin_undo_group ();

  if (count > 1 || rl_explicit_arg)
    rl_kill_text (opoint, rl_point);
  else
    rl_delete_text (opoint, rl_point);


  if (rl_point < rl_end)
    {
      opoint = rl_point;
      _rl_insert_char (l, ' ');
      rl_point = opoint;
    }

  rl_end_undo_group ();

  return 0;
}
