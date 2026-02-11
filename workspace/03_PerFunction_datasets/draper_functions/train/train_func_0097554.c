yylex (YYSTYPE *lvalp, parser_control *pc)
{
  unsigned char c;
  int count;

  for (;;)
    {
      while (c = *pc->input, ISSPACE (c))
	pc->input++;

      if (ISDIGIT (c) || c == '-' || c == '+')
	{
	  char const *p;
	  int sign;
	  int value;
	  if (c == '-' || c == '+')
	    {
	      sign = c == '-' ? -1 : 1;
	      c = *++pc->input;
	      if (! ISDIGIT (c))

		continue;
	    }
	  else
	    sign = 0;
	  p = pc->input;
	  value = 0;
	  do
	    {
	      value = 10 * value + c - '0';
	      c = *++p;
	    }
	  while (ISDIGIT (c));
	  lvalp->textintval.value = sign < 0 ? -value : value;
	  lvalp->textintval.digits = p - pc->input;
	  pc->input = p;
	  return sign ? tSNUMBER : tUNUMBER;
	}

      if (ISALPHA (c))
	{
	  char buff[20];
	  char *p = buff;
	  table const *tp;

	  do
	    {
	      if (p < buff + sizeof buff - 1)
		*p++ = c;
	      c = *++pc->input;
	    }
	  while (ISALPHA (c) || c == '.');

	  *p = '\0';
	  tp = lookup_word (pc, buff);
	  if (! tp)
	    return '?';
	  lvalp->intval = tp->value;
	  return tp->type;
	}

      if (c != '(')
	return *pc->input++;
      count = 0;
      do
	{
	  c = *pc->input++;
	  if (c == '\0')
	    return c;
	  if (c == '(')
	    count++;
	  else if (c == ')')
	    count--;
	}
      while (count > 0);
    }
}
