genie_log_long_mp (NODE_T * p)
{
  int digits = get_mp_digits (MOID (p)), size = get_mp_size (MOID (p));
  ADDR_T pop_sp = stack_pointer;
  MP_T *x = (MP_T *) STACK_OFFSET (-size);
  PRELUDE_ERROR (log_mp (p, x, x, digits) == NO_MP, p, ERROR_INVALID_ARGUMENT, MOID (p));
  MP_STATUS (x) = (MP_T) INIT_MASK;
  stack_pointer = pop_sp;
}
