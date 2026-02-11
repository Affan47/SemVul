mpz_poly_mul_karatsuba(mpz_poly_t res, mpz_poly_t poly1,
                            mpz_poly_t poly2)
{
   if (!poly1->length || !poly2->length)
   {

      res->length = 0;
      return;
   }

   if (poly1 == poly2)
   {

      mpz_poly_sqr_karatsuba(res, poly1);
      return;
   }


   if (poly1->length > poly2->length)
      SWAP_MPZ_POLY_PTRS(poly1, poly2);


   unsigned long length = poly1->length + poly2->length - 1;
   unsigned long limbs = mpz_poly_product_max_limbs(poly1, poly2);


   mpz_t* scratch = (mpz_t*)
                     flint_stack_alloc_bytes((length+1) * sizeof(mpz_t));
   for (unsigned long i = 0; i <= length; i++)
      mpz_init2(scratch[i], limbs * FLINT_BITS);


   unsigned long crossover = _mpz_poly_mul_karatsuba_crossover(limbs/2);

   if (res == poly1 || res == poly2)
   {

      mpz_poly_t temp;
      mpz_poly_init3(temp, length, FLINT_BITS*limbs);

      _mpz_poly_mul_kara_recursive(
            temp->coeffs, poly1->coeffs, poly1->length,
            poly2->coeffs, poly2->length, scratch, 1, crossover);

      mpz_poly_swap(temp, res);
      mpz_poly_clear(temp);
   }
   else
   {


      mpz_poly_ensure_alloc(res, length);

      _mpz_poly_mul_kara_recursive(
            res->coeffs, poly1->coeffs, poly1->length,
            poly2->coeffs, poly2->length, scratch, 1, crossover);
   }

   res->length = length;

   for (unsigned long i = 0; i <= length; i++)
      mpz_clear(scratch[i]);
   flint_stack_release();
}
