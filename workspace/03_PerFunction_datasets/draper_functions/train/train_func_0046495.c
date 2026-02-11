xtensa_clear_insn_labels (void)
{
  sym_list **pl;

  for (pl = &free_insn_labels; *pl != NULL; pl = &(*pl)->next)
    ;
  *pl = insn_labels;
  insn_labels = NULL;
}
