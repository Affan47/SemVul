find_formats ()
{
  int i;

  for (i = 0; i < NUM_RTX_CODE; i++)
    {
      const char **f;

      if (special_format (defs[i].format))
	continue;

      for (f = formats; *f; f++)
	if (! strcmp (*f, defs[i].format))
	  break;

      if (*f == 0)
	*f = defs[i].format;
    }
}
