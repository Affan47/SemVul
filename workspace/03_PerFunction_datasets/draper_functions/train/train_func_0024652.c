_mpz_poly_sqr_classical(mpz_poly_t res, mpz_poly_t poly)
{
   FLINT_ASSERT(res != poly);
   FLINT_ASSERT(poly->length);

   res->length = 2*poly->length - 1;
   FLINT_ASSERT(res->alloc >= res->length);

   for (unsigned long i = 0; i < res->length; i++)
      mpz_set_ui(res->coeffs[i], 0);


   for (unsigned long i = 1; i < poly->length; i++)
      for (unsigned long j = 0; j < i; j++)
         mpz_addmul(res->coeffs[i+j], poly->coeffs[i], poly->coeffs[j]);


   for (unsigned long i = 1; i < res->length - 1; i++)
      mpz_add(res->coeffs[i], res->coeffs[i], res->coeffs[i]);


   for (unsigned long i = 0; i < poly->length; i++)
      mpz_addmul(res->coeffs[2*i], poly->coeffs[i], poly->coeffs[i]);
}
