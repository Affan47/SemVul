neon_struct_operand (rtx op, enum machine_mode mode ATTRIBUTE_UNUSED)
{
  return ((GET_CODE (op) == MEM) && (
#line 653 "../../src/gcc/config/arm/predicates.md"
(TARGET_32BIT && neon_vector_mem_operand (op, 2)))) && (
(mode == VOIDmode || GET_MODE (op) == mode));
}
