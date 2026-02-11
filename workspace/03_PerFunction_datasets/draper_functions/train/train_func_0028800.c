rl_vi_char_search (count, key)
     int count, key;
{
  int c;
#if defined (HANDLE_MULTIBYTE)
  static char *target;
  static int tlen;
#else
  static char target;
#endif

  if (key == ';' || key == ',')
    _rl_cs_dir = (key == ';') ? _rl_cs_orig_dir : -_rl_cs_orig_dir;
  else
    {
      switch (key)
        {
        case 't':
          _rl_cs_orig_dir = _rl_cs_dir = FTO;
          break;

        case 'T':
          _rl_cs_orig_dir = _rl_cs_dir = BTO;
          break;

        case 'f':
          _rl_cs_orig_dir = _rl_cs_dir = FFIND;
          break;

        case 'F':
          _rl_cs_orig_dir = _rl_cs_dir = BFIND;
          break;
        }

      if (vi_redoing)
	{

	}
#if defined (READLINE_CALLBACKS)
      else if (RL_ISSTATE (RL_STATE_CALLBACK))
        {
          _rl_callback_data = _rl_callback_data_alloc (count);
          _rl_callback_data->i1 = _rl_cs_dir;
          _rl_callback_func = _rl_vi_callback_char_search;
          return (0);
        }
#endif
      else
	{
#if defined (HANDLE_MULTIBYTE)
	  c = _rl_read_mbchar (_rl_vi_last_search_mbchar, MB_LEN_MAX);
	  if (c <= 0)
	    return -1;
	  _rl_vi_last_search_mblen = c;
#else
	  RL_SETSTATE(RL_STATE_MOREINPUT);
	  c = rl_read_key ();
	  RL_UNSETSTATE(RL_STATE_MOREINPUT);
	  if (c < 0)
	    return -1;
	  _rl_vi_last_search_char = c;
#endif
	}
    }

#if defined (HANDLE_MULTIBYTE)
  target = _rl_vi_last_search_mbchar;
  tlen = _rl_vi_last_search_mblen;
#else
  target = _rl_vi_last_search_char;
#endif

#if defined (HANDLE_MULTIBYTE)
  return (_rl_char_search_internal (count, _rl_cs_dir, target, tlen));
#else
  return (_rl_char_search_internal (count, _rl_cs_dir, target));
#endif
}
