expand_builtin_dwarf_sp_column (void)
{
  unsigned int dwarf_regnum = DWARF_FRAME_REGNUM (STACK_POINTER_REGNUM);
  return GEN_INT (DWARF2_FRAME_REG_OUT (dwarf_regnum, 1));
}
