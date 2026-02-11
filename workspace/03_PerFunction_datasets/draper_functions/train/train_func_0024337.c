_has_value (char **src, const char *tgt)
{
  char **p;

  for (p = src; *p != NULL; p++)
    {
      if (!strcasecmp (*p, tgt))
	{
	  return 1;
	}
    }

  return 0;
}
