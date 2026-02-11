mpz_poly_sqr_classical(mpz_poly_t res, mpz_poly_t poly)
{
   if (!poly->length)
   {

      res->length = 0;
      return;
   }

   unsigned long limbs = mpz_poly_product_max_limbs(poly, poly);
   unsigned long length = 2*poly->length - 1;

   if (res == poly)
   {

      mpz_poly_t temp;
      mpz_poly_init3(temp, length, FLINT_BITS * limbs);
      _mpz_poly_sqr_classical(temp, poly);
      mpz_poly_swap(temp, res);
      mpz_poly_clear(temp);
   }
   else
   {


      mpz_poly_ensure_alloc(res, length);
      _mpz_poly_sqr_classical(res, poly);
   }
}
