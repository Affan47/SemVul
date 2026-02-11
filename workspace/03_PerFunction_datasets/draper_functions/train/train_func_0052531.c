vsib_address_operand (rtx op, enum machine_mode mode ATTRIBUTE_UNUSED)
{
  return ((
#line 831 "../../src/gcc/config/i386/predicates.md"
(address_operand (op, VOIDmode))) && (
(vsib_address_operand_1 (op, mode)))) && (
(mode == VOIDmode || GET_MODE (op) == mode));
}
