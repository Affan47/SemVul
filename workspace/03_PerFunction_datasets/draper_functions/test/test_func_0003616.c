get_base_filename (const char *filename)
{
  const char *p = getenv ("COLLECT_GCC_OPTIONS");
  const char *output = NULL;
  int compiling = 0;

  while (p && *p)
    {
      const char *q = extract_string (&p);

      if (strcmp (q, "-o") == 0)
	{
	  if (flag_compare_debug)


	    output = concat (aux_base_name, ".o", NULL);
	  else
	    output = extract_string (&p);
	}
      else if (strcmp (q, "-c") == 0)
	compiling = 1;
    }

  if (compiling && output)
    return output;

  if (p && ! compiling)
    {
      warning (0, "-frepo must be used with -c");
      flag_use_repository = 0;
      return NULL;
    }

  return lbasename (filename);
}
