F_mpz_poly_get_coeff_ui(const F_mpz_poly_t poly, const ulong n)
{
   if (n + 1 > poly->length)
      return 0;

	return F_mpz_get_ui(poly->coeffs + n);
}
