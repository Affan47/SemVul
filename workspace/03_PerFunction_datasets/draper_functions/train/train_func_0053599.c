real_maxval (REAL_VALUE_TYPE *r, int sign, enum machine_mode mode)
{
  const struct real_format *fmt;
  int np2;

  fmt = REAL_MODE_FORMAT (mode);
  if (fmt == NULL)
    abort ();

  r->class = rvc_normal;
  r->sign = sign;
  r->signalling = 0;
  r->canonical = 0;
  r->exp = fmt->emax * fmt->log2_b;

  np2 = SIGNIFICAND_BITS - fmt->p * fmt->log2_b;
  memset (r->sig, -1, SIGSZ * sizeof (unsigned long));
  clear_significand_below (r, np2);
}
