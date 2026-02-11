d_number (struct d_info *di)
{
  int negative;
  char peek;
  long ret;

  negative = 0;
  peek = d_peek_char (di);
  if (peek == 'n')
    {
      negative = 1;
      d_advance (di, 1);
      peek = d_peek_char (di);
    }

  ret = 0;
  while (1)
    {
      if (! IS_DIGIT (peek))
	{
	  if (negative)
	    ret = - ret;
	  return ret;
	}
      ret = ret * 10 + peek - '0';
      d_advance (di, 1);
      peek = d_peek_char (di);
    }
}
