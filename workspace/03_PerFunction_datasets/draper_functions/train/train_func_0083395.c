cselib_process_insn (insn)
     rtx insn;
{
  int i;
  rtx x;

  if (find_reg_note (insn, REG_LIBCALL, NULL))
    cselib_current_insn_in_libcall = true;
  if (find_reg_note (insn, REG_RETVAL, NULL))
    cselib_current_insn_in_libcall = false;
  cselib_current_insn = insn;


  if (GET_CODE (insn) == CODE_LABEL
      || (GET_CODE (insn) == CALL_INSN
	  && find_reg_note (insn, REG_SETJMP, NULL))
      || (GET_CODE (insn) == INSN
	  && GET_CODE (PATTERN (insn)) == ASM_OPERANDS
	  && MEM_VOLATILE_P (PATTERN (insn))))
    {
      clear_table (0);
      return;
    }

  if (! INSN_P (insn))
    {
      cselib_current_insn = 0;
      return;
    }


  if (GET_CODE (insn) == CALL_INSN)
    {
      for (i = 0; i < FIRST_PSEUDO_REGISTER; i++)
	if (call_used_regs[i])
	  cselib_invalidate_regno (i, reg_raw_mode[i]);

      if (! CONST_OR_PURE_CALL_P (insn))
	cselib_invalidate_mem (callmem);
    }

  cselib_record_sets (insn);

#ifdef AUTO_INC_DEC


  for (x = REG_NOTES (insn); x; x = XEXP (x, 1))
    if (REG_NOTE_KIND (x) == REG_INC)
      cselib_invalidate_rtx (XEXP (x, 0));
#endif


  if (GET_CODE (insn) == CALL_INSN)
    for (x = CALL_INSN_FUNCTION_USAGE (insn); x; x = XEXP (x, 1))
      if (GET_CODE (XEXP (x, 0)) == CLOBBER)
	cselib_invalidate_rtx (XEXP (XEXP (x, 0), 0));

  cselib_current_insn = 0;

  if (n_useless_values > MAX_USELESS_VALUES)
    remove_useless_values ();
}
