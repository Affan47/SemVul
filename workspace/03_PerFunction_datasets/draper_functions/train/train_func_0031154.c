nonmemory_operand (rtx op, enum machine_mode mode)
{
  if (CONSTANT_P (op))
    return immediate_operand (op, mode);

  if (GET_MODE (op) != mode && mode != VOIDmode)
    return 0;

  if (GET_CODE (op) == SUBREG)
    {


      if (! reload_completed && MEM_P (SUBREG_REG (op)))
	return general_operand (op, mode);
      op = SUBREG_REG (op);
    }


  return (REG_P (op)
	  && (REGNO (op) >= FIRST_PSEUDO_REGISTER
	      || REGNO_REG_CLASS (REGNO (op)) != NO_REGS));
}
