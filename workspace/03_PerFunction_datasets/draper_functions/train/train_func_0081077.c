gf_w128_composite_multiply_region(gf_t *gf, void *src, void *dest, gf_val_128_t val, int bytes, int xor)
{
  gf_internal_t *h = (gf_internal_t *) gf->scratch;
  gf_t *base_gf = h->base_gf;
  uint64_t b0 = val[1];
  uint64_t b1 = val[0];
  uint64_t *s64, *d64;
  uint64_t *top;
  uint64_t a0, a1, a1b1;
  gf_region_data rd;

  if (val[0] == 0 && val[1] == 0) { gf_multby_zero(dest, bytes, xor); return; }

  gf_set_region_data(&rd, gf, src, dest, bytes, 0, xor, 8);

  s64 = rd.s_start;
  d64 = rd.d_start;
  top = rd.d_top;

  if (xor) {
    while (d64 < top) {
      a1 = s64[0];
      a0 = s64[1];
      a1b1 = base_gf->multiply.w64(base_gf, a1, b1);

      d64[1] ^= (base_gf->multiply.w64(base_gf, a0, b0) ^ a1b1);
      d64[0] ^= (base_gf->multiply.w64(base_gf, a1, b0) ^
          base_gf->multiply.w64(base_gf, a0, b1) ^
          base_gf->multiply.w64(base_gf, a1b1, h->prim_poly));
      s64 += 2;
      d64 += 2;
    }
  } else {
    while (d64 < top) {
      a1 = s64[0];
      a0 = s64[1];
      a1b1 = base_gf->multiply.w64(base_gf, a1, b1);

      d64[1] = (base_gf->multiply.w64(base_gf, a0, b0) ^ a1b1);
      d64[0] = (base_gf->multiply.w64(base_gf, a1, b0) ^
          base_gf->multiply.w64(base_gf, a0, b1) ^
          base_gf->multiply.w64(base_gf, a1b1, h->prim_poly));
      s64 += 2;
      d64 += 2;
    }
  }
}
