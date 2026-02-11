_rl_find_next_mbchar_internal (string, seed, count, find_non_zero)
     char *string;
     int seed, count, find_non_zero;
{
  size_t tmp, len;
  mbstate_t ps;
  int point;
  wchar_t wc;

  tmp = 0;

  memset(&ps, 0, sizeof (mbstate_t));
  if (seed < 0)
    seed = 0;
  if (count <= 0)
    return seed;

  point = seed + _rl_adjust_point (string, seed, &ps);


  if (seed < point)
    count--;

  while (count > 0)
    {
      len = strlen (string + point);
      if (len == 0)
	break;
      tmp = mbrtowc (&wc, string+point, len, &ps);
      if (MB_INVALIDCH ((size_t)tmp))
	{

	  point++;
	  count--;

	  memset(&ps, 0, sizeof(mbstate_t));
	}
      else if (MB_NULLWCH (tmp))
	break;
      else
	{

	  point += tmp;
	  if (find_non_zero)
	    {
	      if (wcwidth (wc) == 0)
		continue;
	      else
		count--;
	    }
	  else
	    count--;
	}
    }

  if (find_non_zero)
    {
      tmp = mbrtowc (&wc, string + point, strlen (string + point), &ps);
      while (MB_NULLWCH (tmp) == 0 && MB_INVALIDCH (tmp) == 0 && wcwidth (wc) == 0)
	{
	  point += tmp;
	  tmp = mbrtowc (&wc, string + point, strlen (string + point), &ps);
	}
    }

  return point;
}
