rl_forward_char (count, key)
     int count, key;
{
  int point;

  if (MB_CUR_MAX == 1 || rl_byte_oriented)
    return (rl_forward_byte (count, key));

  if (count < 0)
    return (rl_backward_char (-count, key));

  if (count > 0)
    {
      if (rl_point == rl_end && EMACS_MODE())
	{
	  rl_ding ();
	  return 0;
	}

      point = _rl_find_next_mbchar (rl_line_buffer, rl_point, count, MB_FIND_NONZERO);

#if defined (VI_MODE)
      if (point >= rl_end && VI_COMMAND_MODE())
	point = _rl_find_prev_mbchar (rl_line_buffer, rl_end, MB_FIND_NONZERO);
#endif

      if (rl_point == point)
	rl_ding ();

      rl_point = point;

      if (rl_end < 0)
	rl_end = 0;
    }

  return 0;
}
