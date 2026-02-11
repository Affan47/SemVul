setup_option (char *p, char *end)
{
  int arg = 0;
  if (*p != '-')
    abort ();

  while (*end == ':')
    {
      *end-- = '\0';
      arg++;
    }

  if (arg > 2)
    abort ();

  while (p)
    {
      unsigned char short_opt = 0;
      const char *long_opt = NULL;

      if (*p++ != '-')
	abort ();
      if (*p == '-')
	{
	  ++p;
	  long_opt = strsep (&p, "|");
	}
      else
	{
	  short_opt = *p++;
	  if (!*p)
	    p = NULL;
	  else if (*p++ != '|')
	    abort ();
	}

      if (long_opt)
	{
	  struct long_option *opt = malloc (sizeof (struct long_option));
	  opt->name = strdup (long_opt);
	  opt->arg = arg;
	  opt->next = long_opts;
	  long_opts = opt;
	}
      else
	short_opts[(unsigned char) short_opt] = arg;
    }
}
