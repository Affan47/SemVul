long_bits_to_long_int (NODE_T * p, MP_T * z, char *str, MOID_T * m)
{
  int base = 0;
  char *radix = NO_TEXT;
  RESET_ERRNO;
  base = (int) a68g_strtoul (str, &radix, 10);
  if (radix != NO_TEXT && TO_UPPER (radix[0]) == TO_UPPER (RADIX_CHAR) && errno == 0) {
    int digits = get_mp_digits (m);
    ADDR_T pop_sp = stack_pointer;
    MP_T *v;
    MP_T *w;
    char *q = radix;
    STACK_MP (v, p, digits);
    STACK_MP (w, p, digits);
    while (q[0] != NULL_CHAR) {
      q++;
    }
    SET_MP_ZERO (z, digits);
    (void) set_mp_short (w, (MP_T) 1, 0, digits);
    if (base < 2 || base > 16) {
      diagnostic_node (A68_RUNTIME_ERROR, p, ERROR_INVALID_RADIX, base);
      exit_genie (p, A68_RUNTIME_ERROR);
    }
    while ((--q) != radix) {
      int digit = char_value (q[0]);
      if (digit >= 0 && digit < base) {
        (void) mul_mp_digit (p, v, w, (MP_T) digit, digits);
        (void) add_mp (p, z, z, v, digits);
      } else {
        diagnostic_node (A68_RUNTIME_ERROR, p, ERROR_IN_DENOTATION, m);
        exit_genie (p, A68_RUNTIME_ERROR);
      }
      (void) mul_mp_digit (p, w, w, (MP_T) base, digits);
    }
    check_long_bits_value (p, z, m);
    stack_pointer = pop_sp;
  } else {
    diagnostic_node (A68_RUNTIME_ERROR, p, ERROR_IN_DENOTATION, m);
    exit_genie (p, A68_RUNTIME_ERROR);
  }
}
