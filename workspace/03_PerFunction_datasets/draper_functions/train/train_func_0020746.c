const_0_to_255_mul_8_operand_1 (rtx op, enum machine_mode mode ATTRIBUTE_UNUSED)
#line 637 "../../src/gcc/config/i386/predicates.md"
{
  unsigned HOST_WIDE_INT val = INTVAL (op);
  return val <= 255*8 && val % 8 == 0;
}
