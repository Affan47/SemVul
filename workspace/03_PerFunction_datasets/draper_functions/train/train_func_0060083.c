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

      point = _rl_forward_char_internal (count);

      if (rl_point == point)
	rl_ding ();

      rl_point = point;
    }

  return 0;
}
