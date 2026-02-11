emit (rtx x)
{
  enum rtx_code code = classify_insn (x);

  switch (code)
    {
    case CODE_LABEL:
      return emit_label (x);
    case INSN:
      return emit_insn (x);
    case  JUMP_INSN:
      {
	rtx insn = emit_jump_insn (x);
	if (any_uncondjump_p (insn) || GET_CODE (x) == RETURN)
	  return emit_barrier ();
	return insn;
      }
    case CALL_INSN:
      return emit_call_insn (x);
    case DEBUG_INSN:
      return emit_debug_insn (x);
    default:
      gcc_unreachable ();
    }
}
