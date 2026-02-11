get_input_delimiter(const char *s)
{
  if (1 == strlen(s))
    {
      return s[0];
    }
  else
    {
      if ('\\' == s[0])
	{

	  switch (s[1])
	    {
	    case 'a':
	      return '\a';
	    case 'b':
	      return '\b';
	    case 'f':
	      return '\f';
	    case 'n':
	      return '\n';
	    case 'r':
	      return '\r';
	    case 't':
	      return'\t';
	    case 'v':
	      return '\v';
	    case '\\':
	      return '\\';
	    default:
	      return get_char_oct_or_hex_escape(s);
	    }
	}
      else
	{
	  error(1, 0,
		_("Invalid input delimiter specification %s: the delimiter must be either a single character or an escape sequence starting with \\."),
		s);

	  return 0;
	}
    }
}
