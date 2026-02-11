const_double_htab_hash (x)
     const void *x;
{
  rtx value = (rtx) x;
  hashval_t h;

  if (GET_MODE (value) == VOIDmode)
    h = CONST_DOUBLE_LOW (value) ^ CONST_DOUBLE_HIGH (value);
  else
    h = real_hash (CONST_DOUBLE_REAL_VALUE (value));
  return h;
}
