gf_w16_bytwo_p_nosse_multiply_region(gf_t *gf, void *src, void *dest, gf_val_32_t val, int bytes, int xor)
{
  uint64_t *s64, *d64, t1, t2, ta, prod, amask;
  gf_region_data rd;
  struct gf_w16_bytwo_data *btd;

  if (val == 0) { gf_multby_zero(dest, bytes, xor); return; }
  if (val == 1) { gf_multby_one(src, dest, bytes, xor); return; }

  btd = (struct gf_w16_bytwo_data *) ((gf_internal_t *) (gf->scratch))->private;

  gf_set_region_data(&rd, gf, src, dest, bytes, val, xor, 8);
  gf_do_initial_region_alignment(&rd);

  s64 = (uint64_t *) rd.s_start;
  d64 = (uint64_t *) rd.d_start;

  if (xor) {
    while (s64 < (uint64_t *) rd.s_top) {
      prod = 0;
      amask = 0x8000;
      ta = *s64;
      while (amask != 0) {
        AB2(btd->prim_poly, btd->mask1, btd->mask2, prod, t1, t2);
        if (val & amask) prod ^= ta;
        amask >>= 1;
      }
      *d64 ^= prod;
      d64++;
      s64++;
    }
  } else {
    while (s64 < (uint64_t *) rd.s_top) {
      prod = 0;
      amask = 0x8000;
      ta = *s64;
      while (amask != 0) {
        AB2(btd->prim_poly, btd->mask1, btd->mask2, prod, t1, t2);
        if (val & amask) prod ^= ta;
        amask >>= 1;
      }
      *d64 = prod;
      d64++;
      s64++;
    }
  }
  gf_do_final_region_alignment(&rd);
}
