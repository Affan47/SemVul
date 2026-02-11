get_regex_type_synonym(unsigned int ix)
{
  unsigned i;
  int flags;

  if (ix >= N_REGEX_MAP_ENTRIES)
    return -1;

  flags = regex_map[ix].option_val;
  for (i=0u; i<ix; ++i)
    {
      if (flags == regex_map[i].option_val)
	{
	  return i;
	}
    }
  return -1;
}
