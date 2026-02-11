lj_str_bufint(char *p, int32_t k)
{
  uint32_t u = (uint32_t)(k < 0 ? -k : k);
  p += 1+10;
  do { *--p = (char)('0' + u % 10); } while (u /= 10);
  if (k < 0) *--p = '-';
  return p;
}
