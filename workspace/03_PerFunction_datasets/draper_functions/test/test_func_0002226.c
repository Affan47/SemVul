rl_backward_char (count, key)
     int count, key;
{
  int point;

  if (MB_CUR_MAX == 1 || rl_byte_oriented)
    return (rl_backward_byte (count, key));

  if (count < 0)
    return (rl_forward_char (-count, key));

  if (count > 0)
    {
      point = rl_point;

      while (count > 0 && point > 0)
	{
	  point = _rl_find_prev_mbchar (rl_line_buffer, point, MB_FIND_NONZERO);
	  count--;
	}
      if (count > 0)
	{
	  rl_point = 0;
	  rl_ding ();
	}
      else
        rl_point = point;
    }

  return 0;
}
