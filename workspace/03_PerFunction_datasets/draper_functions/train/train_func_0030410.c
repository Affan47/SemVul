count_one_set (regs, insn, x, last_set)
     struct loop_regs *regs;
     rtx insn, x;
     rtx *last_set;
{
  if (GET_CODE (x) == CLOBBER && GET_CODE (XEXP (x, 0)) == REG)


    regs->array[REGNO (XEXP (x, 0))].may_not_optimize = 1;

  if (GET_CODE (x) == SET || GET_CODE (x) == CLOBBER)
    {
      rtx dest = SET_DEST (x);
      while (GET_CODE (dest) == SUBREG
	     || GET_CODE (dest) == ZERO_EXTRACT
	     || GET_CODE (dest) == SIGN_EXTRACT
	     || GET_CODE (dest) == STRICT_LOW_PART)
	dest = XEXP (dest, 0);
      if (GET_CODE (dest) == REG)
	{
	  int i;
	  int regno = REGNO (dest);
	  for (i = 0; i < LOOP_REGNO_NREGS (regno, dest); i++)
	    {


	      if (regs->array[regno].set_in_loop > 0
		  && last_set == 0)
		regs->array[regno+i].may_not_optimize = 1;


	      if (last_set[regno] != 0
		  && reg_used_between_p (dest, last_set[regno], insn))
		regs->array[regno+i].may_not_optimize = 1;
	      if (regs->array[regno+i].set_in_loop < 127)
		++regs->array[regno+i].set_in_loop;
	      last_set[regno+i] = insn;
	    }
	}
    }
}
