element_context(int i)
{
  return (0<i && i<yy_start_stack_depth
	  ? yy_start_stack[yy_start_stack_ptr - i]
	  : 0);
}
