_rl_walphabetic (wchar_t wc)
{
  int c;

  if (iswalnum (wc))
    return (1);

  c = wc & 0177;
  return (_rl_allow_pathname_alphabetic_chars &&
	    strchr (pathname_alphabetic_chars, c) != NULL);
}
