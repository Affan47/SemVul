locate_error (const char *msgid, va_list ap)
{
  tree here = 0, t;
  int plus = 0;
  const char *f;

  for (f = msgid; *f; f++)
    {
      plus = 0;
      if (*f == '%')
	{
	  f++;
	  if (*f == '+')
	    f++, plus = 1;
	  if (*f == '#')
	    f++;

	  switch (*f)
	    {

	    case '%':						break;
	    case 'P':
	    case 'd':	(void) va_arg (ap, int);		break;
	    case 's':	(void) va_arg (ap, char *);		break;
	    case 'L':	(void) va_arg (ap, enum languages);	break;
	    case 'C':
	    case 'O':
	    case 'Q':	(void) va_arg (ap, enum tree_code);	break;


	    case 'A':
	    case 'D':
	    case 'E':
	    case 'F':
	    case 'T':
	    case 'V':
	      t = va_arg (ap, tree);
	      if (!here || plus)
		here = t;
	      break;

	    default:
	      errorcount = 0;
	      internal_error ("unexpected letter `%c' in locate_error\n", *f);
	    }
	}
    }

  if (here == 0)
    here = va_arg (ap, tree);

  return here;
}
