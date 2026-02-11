_fmpz_poly_get_coeff_fmpz(fmpz_t x, const fmpz_poly_t poly, const unsigned long n)
{
   if (n >= poly->length)
   {
      fmpz_set_ui(x, 0);
      return;
   }
   fmpz_set(x, poly->coeffs + n*(poly->limbs + 1));
}
