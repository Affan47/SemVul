control_flow_insn_p (const_rtx insn)
{
  switch (GET_CODE (insn))
    {
    case NOTE:
    case CODE_LABEL:
    case DEBUG_INSN:
      return false;

    case JUMP_INSN:

      return (GET_CODE (PATTERN (insn)) != ADDR_VEC
	      && GET_CODE (PATTERN (insn)) != ADDR_DIFF_VEC);

    case CALL_INSN:


      if ((SIBLING_CALL_P (insn)
	   || find_reg_note (insn, REG_NORETURN, 0))
	  && GET_CODE (PATTERN (insn)) != COND_EXEC)
	return true;


      if (can_nonlocal_goto (insn))
	return true;
      break;

    case INSN:

      if (GET_CODE (PATTERN (insn)) == TRAP_IF
	  && XEXP (PATTERN (insn), 0) == const1_rtx)
	return true;
      if (!cfun->can_throw_non_call_exceptions)
	return false;
      break;

    case BARRIER:


      return false;

    default:
      gcc_unreachable ();
    }

  return can_throw_internal (insn);
}
