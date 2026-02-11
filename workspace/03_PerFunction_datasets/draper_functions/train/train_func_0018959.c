mask_operand_wrap_1 (rtx op, enum machine_mode mode ATTRIBUTE_UNUSED)
#line 876 "../../src/gcc/config/rs6000/predicates.md"
{
  HOST_WIDE_INT c, lsb;

  c = INTVAL (op);

  if ((c & 0x80000001) != 0x80000001)
    return 0;

  c = ~c;
  if (c == 0)
    return 0;

  lsb = c & -c;
  c = ~c;
  c &= -lsb;
  lsb = c & -c;
  return c == -lsb;
}
