alter_predicate_for_insn (pattern, alt, max_op, lineno)
     rtx pattern;
     int alt, max_op, lineno;
{
  const char *fmt;
  enum rtx_code code;
  int i, j, len;

  code = GET_CODE (pattern);
  switch (code)
    {
    case MATCH_OPERAND:
      {
	const char *c = XSTR (pattern, 2);

	if (n_alternatives (c) != 1)
	  {
	    message_with_line (lineno,
			       "too many alternatives for operand %d",
			       XINT (pattern, 0));
	    errors = 1;
	    return NULL;
	  }


	if (c && *c && alt > 1)
	  {
	    size_t c_len = strlen (c);
	    size_t len = alt * (c_len + 1);
	    char *new_c = (char *) xmalloc (len);

	    memcpy (new_c, c, c_len);
	    for (i = 1; i < alt; ++i)
	      {
		new_c[i * (c_len + 1) - 1] = ',';
		memcpy (&new_c[i * (c_len + 1)], c, c_len);
	      }
	    new_c[len - 1] = '\0';
	    XSTR (pattern, 2) = new_c;
	  }
      }


    case MATCH_OPERATOR:
    case MATCH_SCRATCH:
    case MATCH_PARALLEL:
    case MATCH_INSN:
      XINT (pattern, 0) += max_op;
      break;

    default:
      break;
    }

  fmt = GET_RTX_FORMAT (code);
  len = GET_RTX_LENGTH (code);
  for (i = 0; i < len; i++)
    {
      rtx r;

      switch (fmt[i])
	{
	case 'e': case 'u':
	  r = alter_predicate_for_insn (XEXP (pattern, i), alt,
					max_op, lineno);
	  if (r == NULL)
	    return r;
	  break;

	case 'E':
	  for (j = XVECLEN (pattern, i) - 1; j >= 0; --j)
	    {
	      r = alter_predicate_for_insn (XVECEXP (pattern, i, j),
					    alt, max_op, lineno);
	      if (r == NULL)
		return r;
	    }
	  break;

	case 'i': case 'w': case '0': case 's':
	  break;

	default:
	  abort ();
	}
    }

  return pattern;
}
