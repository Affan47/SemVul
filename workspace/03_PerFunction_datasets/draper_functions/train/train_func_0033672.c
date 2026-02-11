F_mpz_poly_mul_SS(F_mpz_poly_t res, const F_mpz_poly_t poly1, const F_mpz_poly_t poly2)
{
	if ((poly1->length == 0) || (poly2->length == 0))
   {
      F_mpz_poly_zero(res);
      return;
   }

	if ((poly1 == res) || (poly2 == res))
	{
		F_mpz_poly_t output;
		F_mpz_poly_init2(output, poly1->length + poly2->length - 1);
		if (poly1->length >= poly2->length) _F_mpz_poly_mul_SS(output, poly1, poly2, 0);
		else _F_mpz_poly_mul_SS(output, poly2, poly1, 0);
		F_mpz_poly_swap(output, res);
		F_mpz_poly_clear(output);
	} else
	{
		if (poly1->length >= poly2->length) _F_mpz_poly_mul_SS(res, poly1, poly2, 0);
		else _F_mpz_poly_mul_SS(res, poly2, poly1, 0);
	}
}
