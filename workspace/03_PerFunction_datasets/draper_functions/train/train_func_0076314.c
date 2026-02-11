get_base_filename (const char *filename)
{
  char *p = getenv ("COLLECT_GCC_OPTIONS");
  char *output = NULL;
  int compiling = 0;

  while (p && *p)
    {
      char *q = extract_string (&p);

      if (strcmp (q, "-o") == 0)
	output = extract_string (&p);
      else if (strcmp (q, "-c") == 0)
	compiling = 1;
      }

  if (compiling && output)
    return output;

  if (p && ! compiling)
    {
      warning ("-frepo must be used with -c");
      flag_use_repository = 0;
      return NULL;
    }

  return lbasename (filename);
}
