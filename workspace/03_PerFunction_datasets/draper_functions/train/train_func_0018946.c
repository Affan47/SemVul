arm_not_immediate_operand (rtx op, enum machine_mode mode ATTRIBUTE_UNUSED)
{
  return (GET_CODE (op) == CONST_INT) && (
#line 141 "../../src/gcc/config/arm/predicates.md"
(const_ok_for_arm (~INTVAL (op))));
}
