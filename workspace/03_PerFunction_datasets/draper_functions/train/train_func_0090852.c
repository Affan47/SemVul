addcstr (str, flag)
     char *str;
     int flag;
{
  char *s, *fstr;
  unsigned char uc;

  for (s = str; s && *s; s++)
    {
      uc = *s;

      if (debug)
	{
	  fstr = getcstr (flag);
	  fprintf(stderr, "added %s for character %s\n", fstr, cdesc(uc));
	}

      lsyntax[uc] |= flag;
    }
}
