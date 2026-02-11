find_reg_equiv_invariant_const (void)
{
  int i;
  bool invariant_p;
  rtx list, insn, note, constant, x;

  for (i = FIRST_PSEUDO_REGISTER; i < reg_equiv_init_size; i++)
    {
      constant = NULL_RTX;
      invariant_p = false;
      for (list = reg_equiv_init[i]; list != NULL_RTX; list = XEXP (list, 1))
	{
	  insn = XEXP (list, 0);
	  note = find_reg_note (insn, REG_EQUIV, NULL_RTX);

	  if (note == NULL_RTX)
	    continue;

	  x = XEXP (note, 0);

	  if (! CONSTANT_P (x)
	      || ! flag_pic || LEGITIMATE_PIC_OPERAND_P (x))
	    {


	      if (memory_operand (x, VOIDmode))
		invariant_p = MEM_READONLY_P (x);
	      else if (function_invariant_p (x))
		{
		  if (GET_CODE (x) == PLUS
		      || x == frame_pointer_rtx || x == arg_pointer_rtx)
		    invariant_p = true;
		  else
		    constant = x;
		}
	    }
	}
      ira_reg_equiv_invariant_p[i] = invariant_p;
      ira_reg_equiv_const[i] = constant;
    }
}
