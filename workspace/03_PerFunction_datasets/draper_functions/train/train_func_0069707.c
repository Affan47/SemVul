aarch64_reg_zero_or_m1_or_1 (rtx op, enum machine_mode mode ATTRIBUTE_UNUSED)
{
  switch (GET_CODE (op))
    {
    case REG:
    case SUBREG:
    case CONST_INT:
      break;
    default:
      return false;
    }
  return (register_operand (op, mode)) || ((
#line 42 "../../src/gcc/config/aarch64/predicates.md"
(op == const0_rtx)) || ((
#line 43 "../../src/gcc/config/aarch64/predicates.md"
(op == constm1_rtx)) || (
#line 44 "../../src/gcc/config/aarch64/predicates.md"
(op == const1_rtx))));
}
