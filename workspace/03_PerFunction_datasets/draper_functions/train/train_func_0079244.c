h8300_eightbit_constant_address_p (rtx x)
{

  const unsigned HOST_WIDE_INT n1 = trunc_int_for_mode (0xff00, HImode);
  const unsigned HOST_WIDE_INT n2 = trunc_int_for_mode (0xffff, HImode);
  const unsigned HOST_WIDE_INT h1 = trunc_int_for_mode (0x00ffff00, SImode);
  const unsigned HOST_WIDE_INT h2 = trunc_int_for_mode (0x00ffffff, SImode);
  const unsigned HOST_WIDE_INT s1 = trunc_int_for_mode (0xffffff00, SImode);
  const unsigned HOST_WIDE_INT s2 = trunc_int_for_mode (0xffffffff, SImode);

  unsigned HOST_WIDE_INT addr;


  if (GET_CODE (x) == SYMBOL_REF)
    return (SYMBOL_REF_FLAGS (x) & SYMBOL_FLAG_EIGHTBIT_DATA) != 0;

  if (GET_CODE (x) != CONST_INT)
    return 0;

  addr = INTVAL (x);

  return (0
	  || ((TARGET_H8300 || TARGET_NORMAL_MODE) && IN_RANGE (addr, n1, n2))
	  || (TARGET_H8300H && IN_RANGE (addr, h1, h2))
	  || (TARGET_H8300S && IN_RANGE (addr, s1, s2)));
}
