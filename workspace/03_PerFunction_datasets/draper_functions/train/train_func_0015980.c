safe_atoi (const char *s)
{
  long lval;
  char *end;

  errno = 0;
  lval = strtol(s, &end, 10);
  if ( (LONG_MAX == lval) || (LONG_MIN == lval) )
    {

      if (errno == ERANGE)
	{

	  error(1, errno, "%s", s);
	}
      else
	{

	  error(1, errno, "%s", s);
	}


    }

  if (lval > INT_MAX || lval < INT_MIN)
    {

      errno = ERANGE;
      error(1, errno, "%s", s);
    }
  else if (*end)
    {
      error(1, errno, "Unexpected suffix %s on %s",
	    quotearg_n_style(0, options.err_quoting_style, end),
	    quotearg_n_style(1, options.err_quoting_style, s));
    }
  else if (end == s)
    {
      error(1, errno, "Expected an integer: %s",
	    quotearg_n_style(0, options.err_quoting_style, s));
    }
  return (int)lval;
}
