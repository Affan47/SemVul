insn_use_p (rtx insn, int regno)
{
  struct reg_use_data *use;

  for (use = INSN_REG_USE_LIST (insn); use != NULL; use = use->next_insn_use)
    if (use->regno == regno)
      return true;
  return false;
}
