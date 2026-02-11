gen_rtx_CONST_VECTOR (enum machine_mode mode, rtvec v)
{
  rtx inner_zero = CONST0_RTX (GET_MODE_INNER (mode));
  int i;

  for (i = GET_MODE_NUNITS (mode) - 1; i >= 0; i--)
    if (RTVEC_ELT (v, i) != inner_zero)
      return gen_rtx_raw_CONST_VECTOR (mode, v);
  return CONST0_RTX (mode);
}
