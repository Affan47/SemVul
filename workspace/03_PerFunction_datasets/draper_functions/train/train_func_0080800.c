bignum_maybe_new_sign(bignum* x, int negative_p) {
  if ((BIGNUM_NEGATIVE_P(x)) ? negative_p : (!negative_p))
    return (x);
  else {
    GC_BIGNUM(x);
    bignum* result = (allot_bignum((BIGNUM_LENGTH(x)), negative_p));
    bignum_destructive_copy(x, result);
    return (result);
  }
}
