extract_tbr(uint32 insn, bool *invalid)
{
  uint32 ret = ((insn >> 16) & 0x1f) | ((insn >> 6) & 0x3e0);
  if (ret == TB) ret = 0;
  return ret;
}
