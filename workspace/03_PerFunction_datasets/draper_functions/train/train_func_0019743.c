ensure_stack_size (size_t size)
{
  if (size > stack_size)
    {
      stack_size = 2 * stack_size;
      if (stack_size < size)
        stack_size = size;
      stack =
        (struct element_state *)
        xrealloc (stack, stack_size * sizeof (struct element_state));
    }
}
