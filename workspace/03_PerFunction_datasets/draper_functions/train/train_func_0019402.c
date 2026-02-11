set_nothrow_function_flags (void)
{
  rtx insn;

  current_function_nothrow = 1;


  cfun->all_throwers_are_sibcalls = 1;

  if (! flag_exceptions)
    return;

  for (insn = get_insns (); insn; insn = NEXT_INSN (insn))
    if (can_throw_external (insn))
      {
	current_function_nothrow = 0;

	if (GET_CODE (insn) != CALL_INSN || !SIBLING_CALL_P (insn))
	  {
	    cfun->all_throwers_are_sibcalls = 0;
	    return;
	  }
      }

  for (insn = current_function_epilogue_delay_list; insn;
       insn = XEXP (insn, 1))
    if (can_throw_external (insn))
      {
	current_function_nothrow = 0;

	if (GET_CODE (insn) != CALL_INSN || !SIBLING_CALL_P (insn))
	  {
	    cfun->all_throwers_are_sibcalls = 0;
	    return;
	  }
      }
}
