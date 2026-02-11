insn_invalid_p (insn)
     rtx insn;
{
  rtx pat = PATTERN (insn);
  int num_clobbers = 0;


  int icode = recog (pat, insn,
		     (GET_CODE (pat) == SET
		      && ! reload_completed && ! reload_in_progress)
		     ? &num_clobbers : 0);
  int is_asm = icode < 0 && asm_noperands (PATTERN (insn)) >= 0;


  if ((is_asm && ! check_asm_operands (PATTERN (insn)))
      || (!is_asm && icode < 0))
    return 1;


  if (num_clobbers > 0)
    {
      rtx newpat;

      if (added_clobbers_hard_reg_p (icode))
	return 1;

      newpat = gen_rtx_PARALLEL (VOIDmode, rtvec_alloc (num_clobbers + 1));
      XVECEXP (newpat, 0, 0) = pat;
      add_clobbers (newpat, icode);
      PATTERN (insn) = pat = newpat;
    }


  if (reload_completed)
    {
      extract_insn (insn);

      if (! constrain_operands (1))
	return 1;
    }

  INSN_CODE (insn) = icode;
  return 0;
}
