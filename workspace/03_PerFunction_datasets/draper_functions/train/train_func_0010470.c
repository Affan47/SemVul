zmod_poly_mul(zmod_poly_t res, zmod_poly_t poly1, zmod_poly_t poly2)
{
   if (poly1 == poly2)
   {
      zmod_poly_sqr(res, poly1);
      return;
   }

   if (poly1->length + poly2->length <= 6)
   {
      zmod_poly_mul_classical(res, poly1, poly2);
      return;
   }

   unsigned long bits = FLINT_BIT_COUNT(poly1->p);
   if ((bits <= 32) && (poly1->length + poly2->length <= 8))
   {
      zmod_poly_mul_classical(res, poly1, poly2);
      return;
   }

   zmod_poly_mul_KS(res, poly1, poly2, 0);
}
