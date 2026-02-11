genie_set_bits (NODE_T * p)
{
  A68_BITS j;
  A68_INT i;
  int n;
  unsigned mask = 0x1;
  POP_OBJECT (p, &j, A68_BITS);
  POP_OBJECT (p, &i, A68_INT);
  PRELUDE_ERROR (VALUE (&i) < 1 || VALUE (&i) > BITS_WIDTH, p, ERROR_OUT_OF_BOUNDS, MODE (INT));
  for (n = 0; n < (BITS_WIDTH - VALUE (&i)); n++) {
    mask = mask << 1;
  }
  PUSH_PRIMITIVE (p, VALUE (&j) | mask, A68_BITS);
}
