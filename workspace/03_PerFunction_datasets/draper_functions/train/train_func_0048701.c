rl_vi_append_mode (count, key)
     int count, key;
{
  if (rl_point < rl_end)
    {
      if (MB_CUR_MAX == 1 || rl_byte_oriented)
	rl_point++;
      else
        {
          int point = rl_point;
          rl_forward_char (1, key);
          if (point == rl_point)
            rl_point = rl_end;
        }
    }
  rl_vi_insertion_mode (1, key);
  return (0);
}
