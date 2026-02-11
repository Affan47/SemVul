_rl_char_search_internal (count, dir, smbchar, len)
     int count, dir;
     char *smbchar;
     int len;
#else
_rl_char_search_internal (count, dir, schar)
     int count, dir, schar;
#endif
{
  int pos, inc;
#if defined (HANDLE_MULTIBYTE)
  int prepos;
#endif

  if (dir == 0)
    return -1;

  pos = rl_point;
  inc = (dir < 0) ? -1 : 1;
  while (count)
    {
      if ((dir < 0 && pos <= 0) || (dir > 0 && pos >= rl_end))
	{
	  rl_ding ();
	  return -1;
	}

#if defined (HANDLE_MULTIBYTE)
      pos = (inc > 0) ? _rl_find_next_mbchar (rl_line_buffer, pos, 1, MB_FIND_ANY)
		      : _rl_find_prev_mbchar (rl_line_buffer, pos, MB_FIND_ANY);
#else
      pos += inc;
#endif
      do
	{
#if defined (HANDLE_MULTIBYTE)
	  if (_rl_is_mbchar_matched (rl_line_buffer, pos, rl_end, smbchar, len))
#else
	  if (rl_line_buffer[pos] == schar)
#endif
	    {
	      count--;
	      if (dir < 0)
	        rl_point = (dir == BTO) ? _rl_find_next_mbchar (rl_line_buffer, pos, 1, MB_FIND_ANY)
					: pos;
	      else
		rl_point = (dir == FTO) ? _rl_find_prev_mbchar (rl_line_buffer, pos, MB_FIND_ANY)
					: pos;
	      break;
	    }
#if defined (HANDLE_MULTIBYTE)
	  prepos = pos;
#endif
	}
#if defined (HANDLE_MULTIBYTE)
      while ((dir < 0) ? (pos = _rl_find_prev_mbchar (rl_line_buffer, pos, MB_FIND_ANY)) != prepos
		       : (pos = _rl_find_next_mbchar (rl_line_buffer, pos, 1, MB_FIND_ANY)) != prepos);
#else
      while ((dir < 0) ? pos-- : ++pos < rl_end);
#endif
    }
  return (0);
}
