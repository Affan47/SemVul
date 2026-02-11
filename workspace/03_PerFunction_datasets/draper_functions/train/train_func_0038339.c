vlogical_operand_1 (rtx op, enum machine_mode mode ATTRIBUTE_UNUSED)
#line 104 "../../src/gcc/config/rs6000/predicates.md"
{
  if (GET_CODE (op) == SUBREG)
    op = SUBREG_REG (op);

  if (!REG_P (op))
    return 0;

  if (REGNO (op) > LAST_VIRTUAL_REGISTER)
    return 1;

  return VLOGICAL_REGNO_P (REGNO (op));
}
