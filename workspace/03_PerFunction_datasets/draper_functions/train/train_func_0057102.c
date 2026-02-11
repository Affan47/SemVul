base_alias_check (rtx x, rtx y, enum machine_mode x_mode,
		  enum machine_mode y_mode)
{
  rtx x_base = find_base_term (x);
  rtx y_base = find_base_term (y);


  if (x_base == 0)
    {
      rtx x_c;

      if (! flag_expensive_optimizations || (x_c = canon_rtx (x)) == x)
	return 1;

      x_base = find_base_term (x_c);
      if (x_base == 0)
	return 1;
    }

  if (y_base == 0)
    {
      rtx y_c;
      if (! flag_expensive_optimizations || (y_c = canon_rtx (y)) == y)
	return 1;

      y_base = find_base_term (y_c);
      if (y_base == 0)
	return 1;
    }


  if (rtx_equal_p (x_base, y_base))
    return 1;


  if (GET_CODE (x_base) != ADDRESS && GET_CODE (y_base) != ADDRESS)
    {
      if (GET_CODE (x) == AND && GET_CODE (y) == AND)
	return 1;
      if (GET_CODE (x) == AND
	  && (GET_CODE (XEXP (x, 1)) != CONST_INT
	      || (int) GET_MODE_UNIT_SIZE (y_mode) < -INTVAL (XEXP (x, 1))))
	return 1;
      if (GET_CODE (y) == AND
	  && (GET_CODE (XEXP (y, 1)) != CONST_INT
	      || (int) GET_MODE_UNIT_SIZE (x_mode) < -INTVAL (XEXP (y, 1))))
	return 1;

      return 0;
    }


  if ((GET_CODE (x_base) == ADDRESS && GET_MODE (x_base) == Pmode)
      || (GET_CODE (y_base) == ADDRESS && GET_MODE (y_base) == Pmode))
    return 0;

  if (! flag_argument_noalias)
    return 1;

  if (flag_argument_noalias > 1)
    return 0;


  return ! (GET_MODE (x_base) == VOIDmode && GET_MODE (y_base) == VOIDmode);
}
