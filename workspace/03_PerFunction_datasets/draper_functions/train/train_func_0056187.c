_rl_vi_change_mbchar_case (count)
     int count;
{
  wchar_t wc;
  char mb[MB_LEN_MAX+1];
  int mblen, p;
  mbstate_t ps;

  memset (&ps, 0, sizeof (mbstate_t));
  if (_rl_adjust_point (rl_line_buffer, rl_point, &ps) > 0)
    count--;
  while (count-- && rl_point < rl_end)
    {
      mbrtowc (&wc, rl_line_buffer + rl_point, rl_end - rl_point, &ps);
      if (iswupper (wc))
	wc = towlower (wc);
      else if (iswlower (wc))
	wc = towupper (wc);
      else
	{

	  rl_forward_char (1, 0);
	  continue;
	}


      if (wc)
	{
	  p = rl_point;
	  mblen = wcrtomb (mb, wc, &ps);
	  if (mblen >= 0)
	    mb[mblen] = '\0';
	  rl_begin_undo_group ();
	  rl_vi_delete (1, 0);
	  if (rl_point < p)
	    rl_point++;
	  rl_insert_text (mb);
	  rl_end_undo_group ();
	  rl_vi_check ();
	}
      else
        rl_forward_char (1, 0);
    }

  return 0;
}
