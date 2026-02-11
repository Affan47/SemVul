TrioWriteStringCharacter
TRIO_ARGS3((self, ch, flags),
	   trio_class_t *self,
	   int ch,
	   trio_flags_t flags)
{
  if (flags & FLAGS_ALTERNATIVE)
    {
      if (! isprint(ch))
	{


	  self->OutStream(self, CHAR_BACKSLASH);
	  switch (ch)
	    {
	    case '\007': self->OutStream(self, 'a'); break;
	    case '\b': self->OutStream(self, 'b'); break;
	    case '\f': self->OutStream(self, 'f'); break;
	    case '\n': self->OutStream(self, 'n'); break;
	    case '\r': self->OutStream(self, 'r'); break;
	    case '\t': self->OutStream(self, 't'); break;
	    case '\v': self->OutStream(self, 'v'); break;
	    case '\\': self->OutStream(self, '\\'); break;
	    default:
	      self->OutStream(self, 'x');
	      TrioWriteNumber(self, (trio_uintmax_t)ch,
			      FLAGS_UNSIGNED | FLAGS_NILPADDING,
			      2, 2, BASE_HEX);
	      break;
	    }
	}
      else if (ch == CHAR_BACKSLASH)
	{
	  self->OutStream(self, CHAR_BACKSLASH);
	  self->OutStream(self, CHAR_BACKSLASH);
	}
      else
	{
	  self->OutStream(self, ch);
	}
    }
  else
    {
      self->OutStream(self, ch);
    }
}
