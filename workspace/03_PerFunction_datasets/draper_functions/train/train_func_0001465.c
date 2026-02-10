read_quoted_string (void)
{
  int c;

  while (1)
    {
      c = read_char ();
      if (c == '\\')
	{
	  read_escape ();
	  continue;
	}
      else if (c == '"' || c == EOF)
	break;

      obstack_1grow (&string_obstack, c);
    }

  obstack_1grow (&string_obstack, 0);
  return XOBFINISH (&string_obstack, char *);
}
