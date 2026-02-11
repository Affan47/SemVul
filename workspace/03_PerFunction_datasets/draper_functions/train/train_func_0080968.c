spv_add_sp (spv_t r, spv_t x, sp_t c, spv_size_t len, sp_t m)
{
  spv_size_t i;

  for (i = 0; i < len; i++)
    r[i] = sp_add (x[i], c, m);
}
