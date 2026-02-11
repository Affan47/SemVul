do_print_human  (const void *nodep, VISIT value, int level)
{
  if (value == leaf || value == postorder)
    {
      const char *s = *(const char **) nodep;
      size_t len = strlen (s);
      size_t cnt;

      while (len > 0 && s[len - 1] == '/')
	--len;

      for (cnt = 0; cnt < len; ++cnt)
	if (isalnum (s[cnt]))
	  break;
      if (cnt == len)
	return;

      if (not_first)
	{
	  putchar (',');
	  ++column;

	  if (column > 2 && column + len > 77)
	    {
	      fputs ("\n  ", stdout);
	      column = 2;
	    }
	  else
	    {
	      putchar (' ');
	      ++column;
	    }
	}
      else
	not_first = 1;

      fwrite (s, len, 1, stdout);
      column += len;
    }
}
