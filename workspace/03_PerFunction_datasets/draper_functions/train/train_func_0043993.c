gf_w8_log_divide (gf_t *gf, uint32_t a, uint32_t b)
{
  int log_sum = 0;
  struct gf_w8_logtable_data *ltd;

  if (a == 0 || b == 0) return 0;
  ltd = (struct gf_w8_logtable_data *) ((gf_internal_t *) gf->scratch)->private;

  log_sum = ltd->log_tbl[a] - ltd->log_tbl[b] + (GF_MULT_GROUP_SIZE);
  return (ltd->antilog_tbl[log_sum]);
}
