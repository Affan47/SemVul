call_register_no_elim_operand_1 (rtx op, enum machine_mode mode ATTRIBUTE_UNUSED)
#line 492 "../../../src/gcc/config/i386/predicates.md"
{
  if (GET_CODE (op) == SUBREG)
    op = SUBREG_REG (op);

  if (!TARGET_64BIT && op == stack_pointer_rtx)
    return false;

  return register_no_elim_operand (op, mode);
}
