dwarf2out_stack_adjust (HOST_WIDE_INT offset, const char *label)
{
  if (cfa.reg == STACK_POINTER_REGNUM)
    cfa.offset += offset;

  if (cfa_store.reg == STACK_POINTER_REGNUM)
    cfa_store.offset += offset;

  if (ACCUMULATE_OUTGOING_ARGS)
    return;

#ifndef STACK_GROWS_DOWNWARD
  offset = -offset;
#endif

  args_size += offset;
  if (args_size < 0)
    args_size = 0;

  def_cfa_1 (label, &cfa);
  if (flag_asynchronous_unwind_tables)
    dwarf2out_args_size (label, args_size);
}
