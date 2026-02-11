_cogl_memory_stack_alloc (CoglMemoryStack *stack, size_t bytes)
{
  CoglMemorySubStack *sub_stack;
  void *ret;

  sub_stack = stack->sub_stack;
  if (G_LIKELY (sub_stack->bytes - stack->sub_stack_offset >= bytes))
    {
      ret = sub_stack->data + stack->sub_stack_offset;
      stack->sub_stack_offset += bytes;
      return ret;
    }


  for (sub_stack = _cogl_container_of (sub_stack->link.next, sub_stack, link);
       &sub_stack->link != &stack->sub_stacks;
       sub_stack = _cogl_container_of (sub_stack->link.next, sub_stack, link))
    {
      if (sub_stack->bytes >= bytes)
        {
          ret = sub_stack->data;
          stack->sub_stack = sub_stack;
          stack->sub_stack_offset = bytes;
          return ret;
        }
    }


  sub_stack = _cogl_container_of (stack->sub_stacks.prev, sub_stack, link);

  _cogl_memory_stack_add_sub_stack (stack, MAX (sub_stack->bytes, bytes) * 2);

  sub_stack = _cogl_container_of (stack->sub_stacks.prev, sub_stack, link);

  stack->sub_stack_offset += bytes;

  return sub_stack->data;
}
