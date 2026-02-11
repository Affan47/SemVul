base_name (char const *name)
{
  char const *base = name += FILESYSTEM_PREFIX_LEN (name);
  int all_slashes = 1;
  char const *p;

  for (p = name; *p; p++)
    {
      if (ISSLASH (*p))
	base = p + 1;
      else
	all_slashes = 0;
    }


  if (*base == '\0' && ISSLASH (*name) && all_slashes)
    --base;

  return (char *) base;
}
