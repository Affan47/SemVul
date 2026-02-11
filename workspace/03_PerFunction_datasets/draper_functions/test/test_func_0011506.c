nonimmediate_di_operand_1 (rtx op, enum machine_mode mode ATTRIBUTE_UNUSED)
#line 399 "../../src/gcc/config/arm/predicates.md"
{
   if (s_register_operand (op, mode))
     return true;

   if (GET_CODE (op) == SUBREG)
     op = SUBREG_REG (op);

   return MEM_P (op) && memory_address_p (DImode, XEXP (op, 0));
}
