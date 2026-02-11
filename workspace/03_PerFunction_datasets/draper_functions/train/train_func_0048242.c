makesymlinks (file)
     const char *file;
{
#ifndef PATH_MAX
#define PATH_MAX 4095
#endif
  char *buffer = NULL;
  size_t bufferlen = 0;
  int ret;
  int lineno;
  FILE *fp;

  if (strcmp (file, "-") == 0)
    fp = stdin;
  else
    {
      fp = fopen (file, "r");
      if (fp == NULL)
	{
	  fprintf (stderr, _("%s: file open error: %m\n"), file);
	  return 1;
	}
    }

  ret = 0;
  lineno = 0;
  while (!feof_unlocked (fp))
    {
      ssize_t n = getline (&buffer, &bufferlen, fp);
      char *src;
      char *dest;
      char *cp = buffer;

      if (n < 0)
	break;
      if (buffer[n - 1] == '\n')
	buffer[n - 1] = '\0';

      ++lineno;
      while (isspace (*cp))
	++cp;
      if (*cp == '\0')

	continue;
      src = cp;

      do
	++cp;
      while (*cp != '\0' && ! isspace (*cp));
      if (*cp != '\0')
	*cp++ = '\0';

      while (isspace (*cp))
	++cp;
      if (*cp == '\0')
	{
	  fprintf (stderr, _("No target in line %d\n"), lineno);
	  ret = 1;
	  continue;
	}
      dest = cp;

      do
	++cp;
      while (*cp != '\0' && ! isspace (*cp));
      if (*cp != '\0')
	*cp++ = '\0';

      ret |= makesymlink (src, dest);
    }
  fclose (fp);

  return ret;
}
