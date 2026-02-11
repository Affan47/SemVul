any_uncondjump_p (rtx insn)
{
  rtx x = pc_set (insn);
  if (!x)
    return 0;
  if (GET_CODE (SET_SRC (x)) != LABEL_REF)
    return 0;
  return 1;
}
