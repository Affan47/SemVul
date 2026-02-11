only_leaf_regs_used (void)
{
  int i;
  const char *const permitted_reg_in_leaf_functions = LEAF_REGISTERS;

  for (i = 0; i < FIRST_PSEUDO_REGISTER; i++)
    if ((df_regs_ever_live_p (i) || global_regs[i])
	&& ! permitted_reg_in_leaf_functions[i])
      return 0;

  if (crtl->uses_pic_offset_table
      && pic_offset_table_rtx != 0
      && REG_P (pic_offset_table_rtx)
      && ! permitted_reg_in_leaf_functions[REGNO (pic_offset_table_rtx)])
    return 0;

  return 1;
}
