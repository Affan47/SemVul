_zmod_poly_sub(zmod_poly_t res, zmod_poly_t poly1, zmod_poly_t poly2)
{
   if (poly1 == poly2)
   {

      res->length = 0;
      return;
   }

   int swapped = 0;
   if (poly1->length > poly2->length)
   {
      swapped = 1;
      SWAP_ZMOD_POLY_PTRS(poly1, poly2);
   }

   unsigned long i;

   if (swapped)
   {
      for (i = 0; i < poly1->length; i++)
      {
         res->coeffs[i] = z_submod(poly2->coeffs[i], poly1->coeffs[i], poly2->p);
      }

      for (; i < poly2->length; i++)
         res->coeffs[i] = poly2->coeffs[i];
   }
   else
   {
      for (i = 0; i < poly1->length; i++)
      {
         res->coeffs[i] = z_submod(poly1->coeffs[i], poly2->coeffs[i], poly2->p);
      }

      for (; i < poly2->length; i++)
      {
         res->coeffs[i] = poly2->p - poly2->coeffs[i];
         if (res->coeffs[i] == poly2->p) res->coeffs[i] = 0;
      }
   }

   res->length = poly2->length;
   __zmod_poly_normalise(res);
}
