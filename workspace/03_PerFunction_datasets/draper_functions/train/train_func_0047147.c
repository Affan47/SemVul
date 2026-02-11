default_unspec_may_trap_p (const_rtx x, unsigned flags)
{
  int i;


  if ((SCALAR_FLOAT_MODE_P (GET_MODE (x)) && flag_trapping_math))
    return 1;

  for (i = 0; i < XVECLEN (x, 0); ++i)
    {
      if (may_trap_p_1 (XVECEXP (x, 0, i), flags))
	return 1;
    }

  return 0;
}
