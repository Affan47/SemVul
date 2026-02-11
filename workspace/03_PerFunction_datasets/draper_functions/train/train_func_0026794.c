ext_register_operand_1 (rtx op, enum machine_mode mode ATTRIBUTE_UNUSED)
#line 62 "../../../src/gcc/config/i386/predicates.md"
{
  if ((!TARGET_64BIT || GET_MODE (op) != DImode)
      && GET_MODE (op) != SImode && GET_MODE (op) != HImode)
    return false;
  if (GET_CODE (op) == SUBREG)
    op = SUBREG_REG (op);


  return (REG_P (op)
	  && (REGNO (op) > LAST_VIRTUAL_REGISTER || REGNO (op) <= BX_REG));
}
