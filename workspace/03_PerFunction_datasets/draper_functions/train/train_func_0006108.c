cp_integer(const char *begin, const char *end, int base, int *result)
{
  const char *s = begin;
  bool negative = false;
  if (s + 1 < end && *s == '-' && s[1] != '+') {
    negative = true;
    s++;
  }

  uint32_t value;
  if ((end = cp_integer(s, end, base, &value)) == s)
    return begin;

  uint32_t max = (negative ? 0x80000000U : 0x7FFFFFFFU);
  if (value > max) {
    cp_errno = CPE_OVERFLOW;
    value = max;
  }

  *result = (negative ? -value : value);
  return end;
}
