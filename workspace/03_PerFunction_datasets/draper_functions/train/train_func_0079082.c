zmod_poly_mulmod(zmod_poly_t res, zmod_poly_t poly1, zmod_poly_t poly2, zmod_poly_t f)
{
   unsigned long p = f->p;

   if (f->length == 0)
   {
      printf("FLINT Exception: Divide by zero\n");
      abort();
   }
   if ((f->length == 1) || (poly1->length == 0) || (poly2->length == 0))
   {
      zmod_poly_zero(res);
	  return;
   }

   zmod_poly_t prod, quot;
   zmod_poly_init(prod, p);
   zmod_poly_init(quot, p);
   zmod_poly_mul(prod, poly1, poly2);
   zmod_poly_divrem(quot, res, prod, f);
   zmod_poly_clear(quot);
   zmod_poly_clear(prod);

}
