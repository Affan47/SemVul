next_char_of_string (void)
{
  unsigned int c;

  c = *input_line_pointer++ & CHAR_MASK;
  switch (c)
    {
    case '\"':
      c = NOT_A_CHAR;
      break;

    case '\n':
      as_warn (_("unterminated string; newline inserted"));
      bump_line_counters ();
      break;

#ifndef NO_STRING_ESCAPES
    case '\\':
      switch (c = *input_line_pointer++)
	{
	case 'b':
	  c = '\b';
	  break;

	case 'f':
	  c = '\f';
	  break;

	case 'n':
	  c = '\n';
	  break;

	case 'r':
	  c = '\r';
	  break;

	case 't':
	  c = '\t';
	  break;

	case 'v':
	  c = '\013';
	  break;

	case '\\':
	case '"':
	  break;

	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
	  {
	    long number;
	    int i;

	    for (i = 0, number = 0;
		 ISDIGIT (c) && i < 3;
		 c = *input_line_pointer++, i++)
	      {
		number = number * 8 + c - '0';
	      }

	    c = number & 0xff;
	  }
	  --input_line_pointer;
	  break;

	case 'x':
	case 'X':
	  {
	    long number;

	    number = 0;
	    c = *input_line_pointer++;
	    while (ISXDIGIT (c))
	      {
		if (ISDIGIT (c))
		  number = number * 16 + c - '0';
		else if (ISUPPER (c))
		  number = number * 16 + c - 'A' + 10;
		else
		  number = number * 16 + c - 'a' + 10;
		c = *input_line_pointer++;
	      }
	    c = number & 0xff;
	    --input_line_pointer;
	  }
	  break;

	case '\n':

	  as_warn (_("unterminated string; newline inserted"));
	  c = '\n';
	  bump_line_counters ();
	  break;

	default:

#ifdef ONLY_STANDARD_ESCAPES
	  as_bad (_("bad escaped character in string"));
	  c = '?';
#endif

	  break;
	}
      break;
#endif

    default:
      break;
    }
  return (c);
}
