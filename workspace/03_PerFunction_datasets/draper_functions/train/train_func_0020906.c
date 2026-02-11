gf_general_do_region_multiply(gf_t *gf, gf_general_t *a, void *ra, void *rb, int bytes, int xor)
{
  gf_internal_t *h;
  int w;

  h = (gf_internal_t *) gf->scratch;
  w = h->w;

  if (w <= 32) {
    gf->multiply_region.w32(gf, ra, rb, a->w32, bytes, xor);
  } else if (w <= 64) {
    gf->multiply_region.w64(gf, ra, rb, a->w64, bytes, xor);
  } else {
    gf->multiply_region.w128(gf, ra, rb, a->w128, bytes, xor);
  }
}
