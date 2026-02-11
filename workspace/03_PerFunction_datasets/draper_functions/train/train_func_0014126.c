mbskipname (pat, dname, flags)
     char *pat, *dname;
     int flags;
{
  int ret;
  wchar_t *pat_wc, *dn_wc;
  size_t pat_n, dn_n;

  pat_n = xdupmbstowcs (&pat_wc, NULL, pat);
  dn_n = xdupmbstowcs (&dn_wc, NULL, dname);

  ret = 0;
  if (pat_n != (size_t)-1 && dn_n !=(size_t)-1)
    {


      if (noglob_dot_filenames == 0 && pat_wc[0] != L'.' &&
	    (pat_wc[0] != L'\\' || pat_wc[1] != L'.') &&
	    (dn_wc[0] == L'.' &&
	      (dn_wc[1] == L'\0' || (dn_wc[1] == L'.' && dn_wc[2] == L'\0'))))
	ret = 1;


     else if (noglob_dot_filenames && dn_wc[0] == L'.' &&
	   pat_wc[0] != L'.' &&
	   (pat_wc[0] != L'\\' || pat_wc[1] != L'.'))
	ret = 1;
    }

  FREE (pat_wc);
  FREE (dn_wc);

  return ret;
}
