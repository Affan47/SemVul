over_mp (NODE_T * p, MP_T * z, MP_T * x, MP_T * y, int digits)
{
  int digits_g = FUN_DIGITS (digits);
  MP_T *x_g, *y_g, *z_g;
  ADDR_T pop_sp = stack_pointer;
  if (MP_DIGIT (y, 1) == 0) {
    errno = ERANGE;
    return (NO_MP);
  }
  STACK_MP (x_g, p, digits_g);
  STACK_MP (y_g, p, digits_g);
  STACK_MP (z_g, p, digits_g);
  (void) lengthen_mp (p, x_g, digits_g, x, digits);
  (void) lengthen_mp (p, y_g, digits_g, y, digits);
  (void) div_mp (p, z_g, x_g, y_g, digits_g);
  trunc_mp (p, z_g, z_g, digits_g);
  (void) shorten_mp (p, z, digits, z_g, digits_g);
  MP_STATUS (z) = (MP_T) INIT_MASK;

  stack_pointer = pop_sp;
  return (z);
}
