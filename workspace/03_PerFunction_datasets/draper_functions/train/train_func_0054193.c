gf_w32_shift_multiply (gf_t *gf, uint32_t a32, uint32_t b32)
{
  uint64_t product, i, pp, a, b, one;
  gf_internal_t *h;

  a = a32;
  b = b32;
  h = (gf_internal_t *) gf->scratch;
  one = 1;
  pp = h->prim_poly | (one << 32);

  product = 0;

  for (i = 0; i < GF_FIELD_WIDTH; i++) {
    if (a & (one << i)) product ^= (b << i);
  }
  for (i = (GF_FIELD_WIDTH*2-2); i >= GF_FIELD_WIDTH; i--) {
    if (product & (one << i)) product ^= (pp << (i-GF_FIELD_WIDTH));
  }
  return product;
}
