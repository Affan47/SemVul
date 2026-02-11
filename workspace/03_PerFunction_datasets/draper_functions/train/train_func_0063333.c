mark_reg_conflicts (reg)
     rtx reg;
{
  int regno;

  if (GET_CODE (reg) == SUBREG)
    reg = SUBREG_REG (reg);

  if (GET_CODE (reg) != REG)
    return;

  regno = REGNO (reg);


  if (regno >= FIRST_PSEUDO_REGISTER)
    {
      if (reg_allocno[regno] >= 0)
	record_one_conflict (regno);
    }

  if (reg_renumber[regno] >= 0)
    regno = reg_renumber[regno];


  if (regno < FIRST_PSEUDO_REGISTER && ! fixed_regs[regno])
    {
      int last = regno + HARD_REGNO_NREGS (regno, GET_MODE (reg));
      while (regno < last)
	{
	  record_one_conflict (regno);
	  regno++;
	}
    }
}
