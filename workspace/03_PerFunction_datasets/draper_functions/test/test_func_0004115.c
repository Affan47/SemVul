forget_old_reloads_1 (rtx x, const_rtx ignored ATTRIBUTE_UNUSED,
		      void *data)
{
  unsigned int regno;
  unsigned int nr;
  regset regs = (regset) data;


  while (GET_CODE (x) == SUBREG)
    {


      x = SUBREG_REG (x);
    }

  if (!REG_P (x))
    return;

  regno = REGNO (x);

  if (regno >= FIRST_PSEUDO_REGISTER)
    nr = 1;
  else
    {
      unsigned int i;

      nr = hard_regno_nregs[regno][GET_MODE (x)];


      if (!regs)
	for (i = 0; i < nr; i++)


	  if (n_reloads == 0
	      || ! TEST_HARD_REG_BIT (reg_is_output_reload, regno + i))
	    {
	      CLEAR_HARD_REG_BIT (reg_reloaded_valid, regno + i);
	      spill_reg_store[regno + i] = 0;
	    }
    }

  if (regs)
    while (nr-- > 0)
      SET_REGNO_REG_SET (regs, regno + nr);
  else
    {


      while (nr-- > 0)


	if (n_reloads == 0
	    || !REGNO_REG_SET_P (&reg_has_output_reload, regno + nr))
	  reg_last_reload_reg[regno + nr] = 0;
     }
}
