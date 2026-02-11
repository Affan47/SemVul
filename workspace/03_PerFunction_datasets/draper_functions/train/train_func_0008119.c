reg_is_born (rtx reg, int birth)
{
  int regno;

  if (GET_CODE (reg) == SUBREG)
    {
      regno = REGNO (SUBREG_REG (reg));
      if (regno < FIRST_PSEUDO_REGISTER)
	regno = subreg_hard_regno (reg, 1);
    }
  else
    regno = REGNO (reg);

  if (regno < FIRST_PSEUDO_REGISTER)
    {
      mark_life (regno, GET_MODE (reg), 1);


      if (birth < 2 * this_insn_number)
	post_mark_life (regno, GET_MODE (reg), 1, birth, 2 * this_insn_number);
    }
  else
    {
      if (reg_qty[regno] == -2)
	alloc_qty (regno, GET_MODE (reg), PSEUDO_REGNO_SIZE (regno), birth);


      if (reg_qty[regno] >= 0)
	qty[reg_qty[regno]].death = -1;
    }
}
