reg_or_sub_cint_operand (rtx op, enum machine_mode mode ATTRIBUTE_UNUSED)
{
  return (GET_CODE (op) == CONST_INT) ? (
#line 397 "../../src/gcc/config/rs6000/predicates.md"
((HOST_BITS_PER_WIDE_INT == 32
		  && (mode == SImode || - INTVAL (op) < 0x7fff8000))
		 || ((unsigned HOST_WIDE_INT) (- INTVAL (op)
					       + (mode == SImode
						  ? 0x80000000 : 0x80008000))
		     < (unsigned HOST_WIDE_INT) 0x100000000ll))) : (gpc_reg_operand (op, mode));
}
