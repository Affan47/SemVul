gf_w8_double_table_multiply_region(gf_t *gf, void *src, void *dest, gf_val_32_t val, int bytes, int xor)
{
  uint16_t *base;
  uint32_t b, c, vc, vb;
  gf_internal_t *h;
  struct gf_w8_double_table_data  *dtd;
  struct gf_w8_double_table_lazy_data  *ltd;
  gf_region_data rd;

  if (val == 0) { gf_multby_zero(dest, bytes, xor); return; }
  if (val == 1) { gf_multby_one(src, dest, bytes, xor); return; }

  h = (gf_internal_t *) (gf->scratch);
  if (h->region_type & GF_REGION_LAZY) {
    ltd = (struct gf_w8_double_table_lazy_data *) h->private;
    base = ltd->mult;
    for (b = 0; b < GF_FIELD_SIZE; b++) {
      vb = (ltd->smult[val][b] << 8);
      for (c = 0; c < GF_FIELD_SIZE; c++) {
        vc = ltd->smult[val][c];
        base[(b << 8)| c] = (vb | vc);
      }
    }

  } else {
    dtd = (struct gf_w8_double_table_data *) h->private;
    base = &(dtd->mult[val][0]);
  }

  gf_set_region_data(&rd, gf, src, dest, bytes, val, xor, 8);
  gf_do_initial_region_alignment(&rd);
  gf_two_byte_region_table_multiply(&rd, base);
  gf_do_final_region_alignment(&rd);
}
