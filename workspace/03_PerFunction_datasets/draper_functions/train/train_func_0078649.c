parse_line (const char *fname, int line_num, const char *str)
{
  const char *start;
  const struct cmd *c = 0;
  size_t len;
  size_t i;

  str = skip_ws (str);


  if (*str == '\0' || *str == '#') return;

  start = str;
  str = skip_string (str);
  len = str - start;

  for (i = 0; i < sizeof (cmd) / sizeof (cmd[0]); ++i)
    {
      if (__strncasecmp (start, cmd[i].name, len) == 0
	  && strlen (cmd[i].name) == len)
	{
	  c = &cmd[i];
	  break;
	}
    }
  if (c == NULL)
    {
      char *buf;

      if (__asprintf (&buf, _("%s: line %d: bad command `%s'\n"),
		      fname, line_num, start) < 0)
	return;

      __fxprintf (NULL, "%s", buf);

      free (buf);
      return;
    }


  str = skip_ws (str);

  if (c->cb == CB_arg_trimdomain_list)
    str = arg_trimdomain_list (fname, line_num, str);
  else if (c->cb == CB_arg_spoof)
    str = arg_spoof (fname, line_num, str);
  else if (c->cb == CB_arg_bool)
    str = arg_bool (fname, line_num, str, c->arg);
  else

    return;

  if (!str)
    return;


  while (*str)
    {
      if (!isspace (*str)) {
	if (*str != '#')
	  {
	    char *buf;

	    if (__asprintf (&buf,
			    _("%s: line %d: ignoring trailing garbage `%s'\n"),
			    fname, line_num, str) < 0)
	      break;

	    __fxprintf (NULL, "%s", buf);

	    free (buf);
	  }
	break;
      }
      ++str;
    }
}
