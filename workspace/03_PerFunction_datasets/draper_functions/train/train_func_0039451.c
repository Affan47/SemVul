refmpz_combit (mpz_ptr r, unsigned long bit)
{
  if (mpz_tstbit (r, bit))
    mpz_clrbit (r, bit);
  else
    mpz_setbit (r, bit);
}
