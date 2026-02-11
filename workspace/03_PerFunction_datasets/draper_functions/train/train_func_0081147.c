genie_mul_long_int (NODE_T * p)
{
  MOID_T *m = RHS_MODE (p);
  int digits = get_mp_digits (m), size = get_mp_size (m);
  MP_T *x = (MP_T *) STACK_OFFSET (-2 * size);
  MP_T *y = (MP_T *) STACK_OFFSET (-size);
  (void) mul_mp (p, x, x, y, digits);
  test_long_int_range (p, x, m);
  MP_STATUS (x) = (MP_T) INIT_MASK;
  DECREMENT_STACK_POINTER (p, size);
}
