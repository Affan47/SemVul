compare_for_stack_reg (rtx insn, stack regstack, rtx pat_src)
{
  rtx *src1, *src2;
  rtx src1_note, src2_note;

  src1 = get_true_reg (&XEXP (pat_src, 0));
  src2 = get_true_reg (&XEXP (pat_src, 1));


  if ((! STACK_REG_P (*src1)
       || (STACK_REG_P (*src2)
	   && get_hard_regnum (regstack, *src2) == FIRST_STACK_REG))
      && swap_rtx_condition (insn))
    {
      rtx temp;
      temp = XEXP (pat_src, 0);
      XEXP (pat_src, 0) = XEXP (pat_src, 1);
      XEXP (pat_src, 1) = temp;

      src1 = get_true_reg (&XEXP (pat_src, 0));
      src2 = get_true_reg (&XEXP (pat_src, 1));

      INSN_CODE (insn) = -1;
    }


  src1_note = find_regno_note (insn, REG_DEAD, REGNO (*src1));

  if (STACK_REG_P (*src2))
    src2_note = find_regno_note (insn, REG_DEAD, REGNO (*src2));
  else
    src2_note = NULL_RTX;

  emit_swap_insn (insn, regstack, *src1);

  replace_reg (src1, FIRST_STACK_REG);

  if (STACK_REG_P (*src2))
    replace_reg (src2, get_hard_regnum (regstack, *src2));

  if (src1_note)
    {
      pop_stack (regstack, REGNO (XEXP (src1_note, 0)));
      replace_reg (&XEXP (src1_note, 0), FIRST_STACK_REG);
    }


  if (src2_note
      && ! (STACK_REG_P (*src1) && STACK_REG_P (*src2)
	    && REGNO (*src1) == REGNO (*src2)))
    {


      if (get_hard_regnum (regstack, XEXP (src2_note, 0)) == FIRST_STACK_REG
	  && src1_note)
	{
	  pop_stack (regstack, REGNO (XEXP (src2_note, 0)));
	  replace_reg (&XEXP (src2_note, 0), FIRST_STACK_REG + 1);
	}
      else
	{


	  remove_regno_note (insn, REG_DEAD, REGNO (XEXP (src2_note, 0)));

	  emit_pop_insn (insn, regstack, XEXP (src2_note, 0),
			 EMIT_AFTER);
	}
    }
}
