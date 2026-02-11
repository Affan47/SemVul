gf_w16_group_4_4_region_multiply(gf_t *gf, void *src, void *dest, gf_val_32_t val, int bytes, int xor)
{
  uint16_t p, l, ind, r, a16, p16;
  struct gf_w16_group_4_4_data *d44;
  gf_region_data rd;
  uint16_t *s16, *d16, *top;

  if (val == 0) { gf_multby_zero(dest, bytes, xor); return; }
  if (val == 1) { gf_multby_one(src, dest, bytes, xor); return; }

  gf_internal_t *h = (gf_internal_t *) gf->scratch;
  d44 = (struct gf_w16_group_4_4_data *) h->private;
  gf_w16_group_4_set_shift_tables(d44->shift, val, h);

  gf_set_region_data(&rd, gf, src, dest, bytes, val, xor, 2);
  gf_do_initial_region_alignment(&rd);

  s16 = (uint16_t *) rd.s_start;
  d16 = (uint16_t *) rd.d_start;
  top = (uint16_t *) rd.d_top;

  while (d16 < top) {
    p = 0;
    a16 = *s16;
    p16 = (xor) ? *d16 : 0;
    ind = a16 >> 12;
    a16 <<= 4;
    p = d44->shift[ind];
    r = p & 0xfff;
    l = p >> 12;
    ind = a16 >> 12;
    a16 <<= 4;
    p = (d44->shift[ind] ^ d44->reduce[l] ^ (r << 4));
    r = p & 0xfff;
    l = p >> 12;
    ind = a16 >> 12;
    a16 <<= 4;
    p = (d44->shift[ind] ^ d44->reduce[l] ^ (r << 4));
    r = p & 0xfff;
    l = p >> 12;
    ind = a16 >> 12;
    p = (d44->shift[ind] ^ d44->reduce[l] ^ (r << 4));
    p ^= p16;
    *d16 = p;
    d16++;
    s16++;
  }
  gf_do_final_region_alignment(&rd);
}
