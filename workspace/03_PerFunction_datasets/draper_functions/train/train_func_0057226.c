get_last_insn_anywhere (void)
{
  struct sequence_stack *stack;
  if (get_last_insn ())
    return get_last_insn ();
  for (stack = seq_stack; stack; stack = stack->next)
    if (stack->last != 0)
      return stack->last;
  return 0;
}
