C_in_stackp(C_word x)
{
  C_word *ptr = (C_word *)(C_uword)x;

#if C_STACK_GROWS_DOWNWARD
  return ptr >= C_stack_pointer_test && ptr <= stack_bottom;
#else
  return ptr < C_stack_pointer_test && ptr >= stack_bottom;
#endif
}
