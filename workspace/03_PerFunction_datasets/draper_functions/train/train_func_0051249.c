genie_arccos_complex (NODE_T * p)
{
  A68_REAL *re = (A68_REAL *) (STACK_OFFSET (-2 * ALIGNED_SIZE_OF (A68_REAL)));
  A68_REAL *im = (A68_REAL *) (STACK_OFFSET (-ALIGNED_SIZE_OF (A68_REAL)));
  RESET_ERRNO;
  if (im == 0) {
    VALUE (re) = acos (VALUE (re));
  } else {
    double r = VALUE (re), i = VALUE (im);
    double u = a68g_hypot (r + 1, i), v = a68g_hypot (r - 1, i);
    double a = 0.5 * (u + v), b = 0.5 * (u - v);
    VALUE (re) = acos (b);
    VALUE (im) = -log (a + sqrt (a * a - 1));
  }
  MATH_RTE (p, errno != 0, MODE (REAL), NO_TEXT);
}
