rl_vi_change_to (count, key)
     int count, key;
{
  int c, start_pos;

  if (_rl_uppercase_p (key))
    rl_stuff_char ('$');
  else if (vi_redoing)
    rl_stuff_char (_rl_vi_last_motion);

  start_pos = rl_point;

  if (rl_vi_domove (key, &c))
    {
      rl_ding ();
      return -1;
    }


  if (((strchr (" l|hwW^0bBFT`", c) == 0) && (rl_point >= start_pos)) &&
      (rl_mark < rl_end))
    rl_mark++;


  if ((_rl_to_upper (c) == 'W') && rl_point < start_pos)
    rl_point = start_pos;

  if (vi_redoing)
    {
      if (vi_insert_buffer && *vi_insert_buffer)
	rl_begin_undo_group ();
      rl_delete_text (rl_point, rl_mark);
      if (vi_insert_buffer && *vi_insert_buffer)
	{
	  rl_insert_text (vi_insert_buffer);
	  rl_end_undo_group ();
	}
    }
  else
    {
      rl_begin_undo_group ();
      rl_kill_text (rl_point, rl_mark);

      if (_rl_uppercase_p (key) == 0)
        _rl_vi_doing_insert = 1;
      rl_vi_start_inserting (key, rl_numeric_arg, rl_arg_sign);
    }

  return (0);
}
