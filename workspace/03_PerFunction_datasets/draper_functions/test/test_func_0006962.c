get_regex_type(const char *s)
{
  unsigned i;
  size_t msglen;
  char *buf, *p;

  msglen = 0u;
  for (i=0u; i<N_REGEX_MAP_ENTRIES; ++i)
    {
      if (0 == strcmp(regex_map[i].name, s))
	return regex_map[i].option_val;
      else
	msglen += strlen(quote(regex_map[i].name)) + 2u;
    }


  p = buf = xmalloc(1u + msglen);
  for (i=0u; i<N_REGEX_MAP_ENTRIES; ++i)
    {
      if (i > 0u)
	{
	  strcpy(p, ", ");
	  p += 2;
	}
      p += sprintf(p, "%s", quote(regex_map[i].name));
    }

  error(1, 0, _("Unknown regular expression type %s; valid types are %s."),
	quote(s),
	buf);

  return -1;
}
