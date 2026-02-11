eh_returnjump_p (rtx insn)
{
  if (!JUMP_P (insn))
    return 0;
  return for_each_rtx (&PATTERN (insn), eh_returnjump_p_1, NULL);
}
