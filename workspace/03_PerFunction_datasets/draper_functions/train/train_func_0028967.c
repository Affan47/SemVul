xpw_find_file (char * const * path,
	       const char * name, const char * suffix)
{
  char * res = _pw_find_file (path, name, suffix);

  if (!res)
    {
      char *file;
      file = ALLOCA (char, strlen (name) + (suffix ? strlen (suffix) : 0) + 1);
      sprintf (file, "%s%s",  name, UNNULL (suffix));
      error (1, errno, _("cannot find file `%s'"), quotearg (file));
    }
  return res;
}
