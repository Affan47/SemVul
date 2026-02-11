pop_stack_level (struct stack_level *stack)
{
  struct stack_level *tem = stack;
  struct obstack *obstack = tem->obstack;
  stack = tem->prev;
  obstack_free (obstack, tem);
  return stack;
}
