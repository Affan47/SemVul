mpz_poly_clear(mpz_poly_t poly)
{
   for (long i = 0; i < poly->alloc; i++)
      mpz_clear(poly->coeffs[i]);

   flint_heap_free(poly->coeffs);
}
