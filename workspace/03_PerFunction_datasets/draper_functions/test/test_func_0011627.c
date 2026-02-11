magnitude_cmp(const vnl_bignum& b1, const vnl_bignum& b2)
{
  if (b1.is_infinity()) return b2.is_infinity() ? 0 : 1;
  if (b2.is_infinity()) return -1;
  if (b1.count > b2.count) return 1;
  if (b2.count > b1.count) return -1;
  Counter i = b1.count;
  while (i > 0) {
    if (b1.data[i - 1] > b2.data[i - 1])
      return 1;
    else if (b1.data[i - 1] < b2.data[i - 1])
      return -1;
    i--;
  }
  return 0;
}
