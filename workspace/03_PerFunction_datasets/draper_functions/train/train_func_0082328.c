replace_rtx (rtx x, rtx from, rtx to)
{
  int i, j;
  const char *fmt;


  if (x != 0 && GET_CODE (x) == CONST_DOUBLE)
    return x;

  if (x == from)
    return to;


  if (x == 0)
    return 0;

  if (GET_CODE (x) == SUBREG)
    {
      rtx new = replace_rtx (SUBREG_REG (x), from, to);

      if (GET_CODE (new) == CONST_INT)
	{
	  x = simplify_subreg (GET_MODE (x), new,
			       GET_MODE (SUBREG_REG (x)),
			       SUBREG_BYTE (x));
	  if (! x)
	    abort ();
	}
      else
	SUBREG_REG (x) = new;

      return x;
    }
  else if (GET_CODE (x) == ZERO_EXTEND)
    {
      rtx new = replace_rtx (XEXP (x, 0), from, to);

      if (GET_CODE (new) == CONST_INT)
	{
	  x = simplify_unary_operation (ZERO_EXTEND, GET_MODE (x),
					new, GET_MODE (XEXP (x, 0)));
	  if (! x)
	    abort ();
	}
      else
	XEXP (x, 0) = new;

      return x;
    }

  fmt = GET_RTX_FORMAT (GET_CODE (x));
  for (i = GET_RTX_LENGTH (GET_CODE (x)) - 1; i >= 0; i--)
    {
      if (fmt[i] == 'e')
	XEXP (x, i) = replace_rtx (XEXP (x, i), from, to);
      else if (fmt[i] == 'E')
	for (j = XVECLEN (x, i) - 1; j >= 0; j--)
	  XVECEXP (x, i, j) = replace_rtx (XVECEXP (x, i, j), from, to);
    }

  return x;
}
