fmpz_poly_get_coeff_mpz_read_only(mpz_t x, const fmpz_poly_t poly, const unsigned long n)
{
   if (n >= poly->length)
   {
      x->_mp_alloc = 1;
      x->_mp_d = (mp_limb_t *) &poly;
      x->_mp_size = 0;
   } else
      _fmpz_poly_get_coeff_mpz_read_only(x, poly, n);
}
