mpz_poly_lshift(mpz_poly_t res, mpz_poly_t poly, unsigned long k)
{
   mpz_poly_ensure_alloc(res, poly->length + k);

   if (poly == res)
   {

      for (long i = poly->length - 1; i >= 0; i--)
         mpz_swap(poly->coeffs[i], poly->coeffs[i+k]);

      for (unsigned long i = 0; i < k; i++)
         mpz_set_ui(poly->coeffs[i], 0);
   }
   else
   {

      for (unsigned long i = 0; i < k; i++)
         mpz_set_ui(res->coeffs[i], 0);

      for (unsigned long i = 0; i < poly->length; i++)
         mpz_set(res->coeffs[i + k], poly->coeffs[i]);
   }

   res->length = poly->length + k;
}
