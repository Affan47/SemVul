gf_w32_split_2_32_lazy_multiply_region(gf_t *gf, void *src, void *dest, uint32_t val, int bytes, int xor)
{
  gf_internal_t *h;
  struct gf_split_2_32_lazy_data *ld;
  int i;
  uint32_t pp, v, v2, s, *s32, *d32, *top;
  gf_region_data rd;

  if (val == 0) { gf_multby_zero(dest, bytes, xor); return; }
  if (val == 1) { gf_multby_one(src, dest, bytes, xor); return; }

  gf_set_region_data(&rd, gf, src, dest, bytes, val, xor, 4);
  gf_do_initial_region_alignment(&rd);

  h = (gf_internal_t *) gf->scratch;
  pp = h->prim_poly;

  ld = (struct gf_split_2_32_lazy_data *) h->private;

  if (ld->last_value != val) {
    v = val;
    for (i = 0; i < 16; i++) {
      v2 = (v << 1);
      if (v & GF_FIRST_BIT) v2 ^= pp;
      ld->tables[i][0] = 0;
      ld->tables[i][1] = v;
      ld->tables[i][2] = v2;
      ld->tables[i][3] = (v2 ^ v);
      v = (v2 << 1);
      if (v2 & GF_FIRST_BIT) v ^= pp;
    }
  }
  ld->last_value = val;

  s32 = (uint32_t *) rd.s_start;
  d32 = (uint32_t *) rd.d_start;
  top = (uint32_t *) rd.d_top;

  while (d32 != top) {
    v = (xor) ? *d32 : 0;
    s = *s32;
    i = 0;
    while (s != 0) {
      v ^= ld->tables[i][s&3];
      s >>= 2;
      i++;
    }
    *d32 = v;
    d32++;
    s32++;
  }
  gf_do_final_region_alignment(&rd);
}
