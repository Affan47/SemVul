mark_call (rtx insn)
{
  if (! RTL_CONST_OR_PURE_CALL_P (insn))
    record_last_mem_set_info (insn);
}
