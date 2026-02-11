poly64_iteration(uint64_t key, uint64_t m, uint64_t y)
{
  const uint64_t marker = p64 - 1;
  const uint64_t maxwordrange = 0xffffffff00000000u;

  y = mul_mod_p64(key, y);
  if(m >= maxwordrange)
    {
      y = sum_mod_p64(y, marker);
      y = sum_mod_p64(mul_mod_p64(key, y), m - offset_p64);
    }
  else
    y = sum_mod_p64(y, m);

  return y;
}
