_bfd_elf_default_action_discarded (asection *sec)
{
  if (sec->flags & SEC_DEBUGGING)
    return PRETEND;

  if (strcmp (".eh_frame", sec->name) == 0)
    return 0;

  if (strcmp (".gcc_except_table", sec->name) == 0)
    return 0;

  return COMPLAIN | PRETEND;
}
