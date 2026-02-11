sanity_check(state *s, int condition, char *msg)
{
  if (NULL == s)
    exit(EXIT_FAILURE);

  if (condition)
    {
      if (!(s->mode & mode_silent))
	{
	  print_status("%s: %s", __progname, msg);
	  try_msg();
	}
      exit (EXIT_FAILURE);
    }
}
