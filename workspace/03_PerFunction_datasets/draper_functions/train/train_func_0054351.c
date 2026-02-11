TrioReadChar
TRIO_ARGS4((self, target, flags, width),
	   trio_class_t *self,
	   char *target,
	   trio_flags_t flags,
	   int width)
{
  int i;
  char ch;
  trio_uintmax_t number;

  assert(VALID(self));
  assert(VALID(self->InStream));

  for (i = 0;
       (self->current != EOF) && (i < width);
       i++)
    {
      ch = (char)self->current;
      self->InStream(self, NULL);
      if ((flags & FLAGS_ALTERNATIVE) && (ch == CHAR_BACKSLASH))
	{
	  switch (self->current)
	    {
	    case '\\': ch = '\\'; break;
	    case 'a': ch = '\007'; break;
	    case 'b': ch = '\b'; break;
	    case 'f': ch = '\f'; break;
	    case 'n': ch = '\n'; break;
	    case 'r': ch = '\r'; break;
	    case 't': ch = '\t'; break;
	    case 'v': ch = '\v'; break;
	    default:
	      if (isdigit(self->current))
		{

		  if (!TrioReadNumber(self, &number, 0, 3, BASE_OCTAL))
		    return 0;
		  ch = (char)number;
		}
	      else if (trio_to_upper(self->current) == 'X')
		{

		  self->InStream(self, NULL);
		  if (!TrioReadNumber(self, &number, 0, 2, BASE_HEX))
		    return 0;
		  ch = (char)number;
		}
	      else
		{
		  ch = (char)self->current;
		}
	      break;
	    }
	}

      if (target)
	target[i] = ch;
    }
  return i + 1;
}
