spv_rev (spv_t r, spv_t x, spv_size_t len)
{
  spv_size_t i;

  ASSERT (r >= x + len || x >= r + len);

  for (i = 0; i < len; i++)
    r[i] = x[len - 1 - i];
}
