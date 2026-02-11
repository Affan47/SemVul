F_mpz_poly_reverse(F_mpz_poly_t res, const F_mpz_poly_t poly, const ulong length)
{
   long i;

   F_mpz_poly_fit_length(res, length);

	if (poly != res)
   {
      for (i = 0; i < FLINT_MIN(length, poly->length); i++)
         F_mpz_set(res->coeffs + length - i - 1, poly->coeffs + i);

      for ( ; i < length; i++)
         F_mpz_zero(res->coeffs + length - i - 1);

   } else
   {
      for (i = 0; i < length/2; i++)
      {

			if (length - i - 1 < res->length) F_mpz_swap(res->coeffs + i, res->coeffs + length - i - 1);
			else
			{
				F_mpz_set(res->coeffs + length - i - 1, res->coeffs + i);
			   F_mpz_zero(res->coeffs + i);
		   }
		}

		if ((length & 1) && (i >= poly->length)) F_mpz_zero(res->coeffs + i);
   }

	_F_mpz_poly_set_length(res, length);
   _F_mpz_poly_normalise(res);
}
