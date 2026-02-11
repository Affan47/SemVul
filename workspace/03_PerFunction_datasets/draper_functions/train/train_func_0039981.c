old_insns_match_p (int mode ATTRIBUTE_UNUSED, rtx i1, rtx i2)
{
  rtx p1, p2;


  if (GET_CODE (i1) != GET_CODE (i2))
    return false;


  if (NOTE_INSN_BASIC_BLOCK_P (i1) && NOTE_INSN_BASIC_BLOCK_P (i2))
    return true;

  p1 = PATTERN (i1);
  p2 = PATTERN (i2);

  if (GET_CODE (p1) != GET_CODE (p2))
    return false;


  if (CALL_P (i1))
    {

      rtx n1 = find_reg_note (i1, REG_EH_REGION, 0);
      rtx n2 = find_reg_note (i2, REG_EH_REGION, 0);

      if (!n1 && n2)
	return false;

      if (n1 && (!n2 || XEXP (n1, 0) != XEXP (n2, 0)))
	return false;

      if (!rtx_equal_p (CALL_INSN_FUNCTION_USAGE (i1),
			CALL_INSN_FUNCTION_USAGE (i2))
	  || SIBLING_CALL_P (i1) != SIBLING_CALL_P (i2))
	return false;
    }

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

      if (!hard_reg_set_equal_p (i1_regset, i2_regset))
	return false;
    }
#endif

  if (reload_completed
      ? rtx_renumbered_equal_p (p1, p2) : rtx_equal_p (p1, p2))
    return true;

  return false;
}
