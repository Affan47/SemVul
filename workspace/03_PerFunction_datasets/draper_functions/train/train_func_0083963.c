set_mp_short (MP_T * z, MP_T x, int x_expo, int digits)
{
  MP_T *d = &MP_DIGIT ((z), 2);
  MP_STATUS (z) = (MP_T) INIT_MASK;
  MP_EXPONENT (z) = (MP_T) x_expo;
  MP_DIGIT (z, 1) = (MP_T) x;
  while (--digits) {
    *d++ = (MP_T) 0;
  }
  return (z);
}
