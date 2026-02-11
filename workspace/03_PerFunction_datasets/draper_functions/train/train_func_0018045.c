set_dst_reg_note (rtx insn, enum reg_note kind, rtx datum, rtx dst)
{
  rtx set = single_set (insn);

  if (set && SET_DEST (set) == dst)
    return set_unique_reg_note (insn, kind, datum);
  return NULL_RTX;
}
