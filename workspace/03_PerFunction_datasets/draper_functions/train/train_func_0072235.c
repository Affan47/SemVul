insns_match_p (mode, i1, i2)
     int mode ATTRIBUTE_UNUSED;
     rtx i1, i2;
{
  rtx p1, p2;


  if (GET_CODE (i1) != GET_CODE (i2))
    return false;

  p1 = PATTERN (i1);
  p2 = PATTERN (i2);

  if (GET_CODE (p1) != GET_CODE (p2))
    return false;


  if (GET_CODE (i1) == CALL_INSN
      && (!rtx_equal_p (CALL_INSN_FUNCTION_USAGE (i1),
		        CALL_INSN_FUNCTION_USAGE (i2))
	  || SIBLING_CALL_P (i1) != SIBLING_CALL_P (i2)))
    return false;

#ifdef STACK_REGS


  if ((mode & CLEANUP_POST_REGSTACK) && stack_regs_mentioned (i1))
    {


      rtx note;
      HARD_REG_SET i1_regset, i2_regset;

      CLEAR_HARD_REG_SET (i1_regset);
      CLEAR_HARD_REG_SET (i2_regset);

      for (note = REG_NOTES (i1); note; note = XEXP (note, 1))
	if (REG_NOTE_KIND (note) == REG_DEAD && STACK_REG_P (XEXP (note, 0)))
	  SET_HARD_REG_BIT (i1_regset, REGNO (XEXP (note, 0)));

      for (note = REG_NOTES (i2); note; note = XEXP (note, 1))
	if (REG_NOTE_KIND (note) == REG_DEAD && STACK_REG_P (XEXP (note, 0)))
	  SET_HARD_REG_BIT (i2_regset, REGNO (XEXP (note, 0)));

      GO_IF_HARD_REG_EQUAL (i1_regset, i2_regset, done);

      return false;

    done:
      ;
    }
#endif

  if (reload_completed
      ? rtx_renumbered_equal_p (p1, p2) : rtx_equal_p (p1, p2))
    return true;


  if (!reload_completed)
    {

      rtx equiv1 = find_reg_equal_equiv_note (i1);
      rtx equiv2 = find_reg_equal_equiv_note (i2);

      if (equiv1 && equiv2


	  && (! reload_completed
	      || (CONSTANT_P (XEXP (equiv1, 0))
		  && rtx_equal_p (XEXP (equiv1, 0), XEXP (equiv2, 0)))))
	{
	  rtx s1 = single_set (i1);
	  rtx s2 = single_set (i2);
	  if (s1 != 0 && s2 != 0
	      && rtx_renumbered_equal_p (SET_DEST (s1), SET_DEST (s2)))
	    {
	      validate_change (i1, &SET_SRC (s1), XEXP (equiv1, 0), 1);
	      validate_change (i2, &SET_SRC (s2), XEXP (equiv2, 0), 1);
	      if (! rtx_renumbered_equal_p (p1, p2))
		cancel_changes (0);
	      else if (apply_change_group ())
		return true;
	    }
	}
    }

  return false;
}
