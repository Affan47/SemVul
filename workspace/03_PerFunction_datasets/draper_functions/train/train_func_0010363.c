gf_w8_log_multiply_region(gf_t *gf, void *src, void *dest, uint32_t val, int bytes, int xor)
{
  int i;
  uint8_t lv;
  uint8_t *s8, *d8;
  struct gf_w8_logtable_data *ltd;

  if (val == 0) { gf_multby_zero(dest, bytes, xor); return; }
  if (val == 1) { gf_multby_one(src, dest, bytes, xor); return; }

  ltd = (struct gf_w8_logtable_data *) ((gf_internal_t *) gf->scratch)->private;
  s8 = (uint8_t *) src;
  d8 = (uint8_t *) dest;

  lv = ltd->log_tbl[val];

  if (xor) {
    for (i = 0; i < bytes; i++) {
      d8[i] ^= (s8[i] == 0 ? 0 : ltd->antilog_tbl[lv + ltd->log_tbl[s8[i]]]);
    }
  } else {
    for (i = 0; i < bytes; i++) {
      d8[i] = (s8[i] == 0 ? 0 : ltd->antilog_tbl[lv + ltd->log_tbl[s8[i]]]);
    }
  }
}
