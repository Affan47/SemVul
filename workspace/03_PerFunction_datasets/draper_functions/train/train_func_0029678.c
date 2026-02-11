short_cint_operand (rtx op, enum machine_mode mode ATTRIBUTE_UNUSED)
{
  return (GET_CODE (op) == CONST_INT) && (
#line 151 "../../src/gcc/config/rs6000/predicates.md"
(satisfies_constraint_I (op)));
}
