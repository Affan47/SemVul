mp_copy(const mp_int *from, mp_int *to)
{
  ARGCHK(from != NULL && to != NULL, MP_BADARG);

  if(from == to)
    return MP_OKAY;

  {
    mp_digit   *tmp;


    if(ALLOC(to) >= USED(from)) {
      s_mp_setz(DIGITS(to) + USED(from), ALLOC(to) - USED(from));
      s_mp_copy(DIGITS(from), DIGITS(to), USED(from));

    } else {
      if((tmp = s_mp_alloc(ALLOC(from), sizeof(mp_digit))) == NULL)
	return MP_MEM;

      s_mp_copy(DIGITS(from), tmp, USED(from));

      if(DIGITS(to) != NULL) {
#if MP_CRYPTO
	s_mp_setz(DIGITS(to), ALLOC(to));
#endif
	s_mp_free(DIGITS(to));
      }

      DIGITS(to) = tmp;
      ALLOC(to) = ALLOC(from);
    }


    USED(to) = USED(from);
    SIGN(to) = SIGN(from);
  }

  return MP_OKAY;

}
