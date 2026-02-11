flow_active_insn_p (const_rtx insn)
{
  if (active_insn_p (insn))
    return true;


  if (GET_CODE (PATTERN (insn)) == CLOBBER
      && REG_P (XEXP (PATTERN (insn), 0))
      && REG_FUNCTION_VALUE_P (XEXP (PATTERN (insn), 0)))
    return true;

  return false;
}
