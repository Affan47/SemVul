const_double_htab_eq (const void *x, const void *y)
{
  const_rtx const a = (const_rtx)x, b = (const_rtx)y;

  if (GET_MODE (a) != GET_MODE (b))
    return 0;
  if (GET_MODE (a) == VOIDmode)
    return (CONST_DOUBLE_LOW (a) == CONST_DOUBLE_LOW (b)
	    && CONST_DOUBLE_HIGH (a) == CONST_DOUBLE_HIGH (b));
  else
    return real_identical (CONST_DOUBLE_REAL_VALUE (a),
			   CONST_DOUBLE_REAL_VALUE (b));
}
