compare_version_strings (const char *v1, const char *v2)
{
  int rresult;
  regex_t r;

  if (regcomp (&r, "^([1-9][0-9]*|0)(\\.([1-9][0-9]*|0))*$",
	       REG_EXTENDED | REG_NOSUB) != 0)
    abort ();
  rresult = regexec (&r, v1, 0, NULL, 0);
  if (rresult == REG_NOMATCH)
    fatal_error ("invalid version number %qs", v1);
  else if (rresult != 0)
    abort ();
  rresult = regexec (&r, v2, 0, NULL, 0);
  if (rresult == REG_NOMATCH)
    fatal_error ("invalid version number %qs", v2);
  else if (rresult != 0)
    abort ();

  return strverscmp (v1, v2);
}
