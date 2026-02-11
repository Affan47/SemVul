_rl_char_search (count, fdir, bdir)
     int count, fdir, bdir;
{
  char mbchar[MB_LEN_MAX];
  int mb_len;

  mb_len = _rl_read_mbchar (mbchar, MB_LEN_MAX);

  if (count < 0)
    return (_rl_char_search_internal (-count, bdir, mbchar, mb_len));
  else
    return (_rl_char_search_internal (count, fdir, mbchar, mb_len));
}
