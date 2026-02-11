s_mp_redc(mp_int *T, mp_mont_modulus *mmm)
{
  mp_err res;
  mp_size i;

  i = (MP_USED(&mmm->N) << 1) + 1;
  MP_CHECKOK( s_mp_pad(T, i) );
  for (i = 0; i < MP_USED(&mmm->N); ++i ) {
    mp_digit m_i = MP_DIGIT(T, i) * mmm->n0prime;

    MP_CHECKOK( s_mp_mul_d_add_offset(&mmm->N, m_i, T, i) );
  }
  s_mp_clamp(T);


  s_mp_rshd( T, MP_USED(&mmm->N) );

  if ((res = s_mp_cmp(T, &mmm->N)) >= 0) {

    MP_CHECKOK( s_mp_sub(T, &mmm->N) );
#ifdef DEBUG
    if ((res = mp_cmp(T, &mmm->N)) >= 0) {
      res = MP_UNDEF;
      goto CLEANUP;
    }
#endif
  }
  res = MP_OKAY;
CLEANUP:
  return res;
}
