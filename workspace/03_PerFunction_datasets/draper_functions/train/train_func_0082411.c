promotable_binary_operator (rtx op, enum machine_mode mode ATTRIBUTE_UNUSED)
{
  return ((GET_CODE (op) == PLUS || GET_CODE (op) == MINUS || GET_CODE (op) == AND || GET_CODE (op) == IOR || GET_CODE (op) == XOR || GET_CODE (op) == ASHIFT) || ((GET_CODE (op) == MULT) && (
#line 1174 "../../src/gcc/config/i386/predicates.md"
(TARGET_TUNE_PROMOTE_HIMODE_IMUL)))) && (
(mode == VOIDmode || GET_MODE (op) == mode));
}
