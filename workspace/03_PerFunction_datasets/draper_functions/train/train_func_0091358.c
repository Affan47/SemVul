_fmpz_poly_set_coeff_fmpz(fmpz_poly_t poly, const unsigned long n, fmpz_t x)
{
   FLINT_ASSERT(poly->length > n);
   fmpz_set(poly->coeffs + n*(poly->limbs + 1), x);
   if (fmpz_is_zero(x) && (poly->length == n+1)) _fmpz_poly_normalise(poly);
}
