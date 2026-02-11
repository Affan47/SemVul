ZmodF_poly_IFFT(ZmodF_poly_t poly)
{

   FLINT_ASSERT((4 * poly->n * FLINT_BITS) % (1 << poly->depth) == 0);
   FLINT_ASSERT(poly->scratch_count >= 1);

   if (poly->length && poly->depth)
      _ZmodF_poly_IFFT(poly->coeffs, poly->depth, 1, poly->length,
                      poly->length, 0, 0, poly->n, poly->scratch);
}
