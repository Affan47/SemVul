cp_integer(const char *begin, const char *end, int base, unsigned *result)
{
  const char *s = begin;
  if (s < end && *s == '+')
    s++;

  if ((base == 0 || base == 16) && s + 1 < end && *s == '0'
      && (s[1] == 'x' || s[1] == 'X')) {
    s += 2;
    base = 16;
  } else if (base == 0 && s < end && *s == '0')
    base = 8;
  else if (base == 0)
    base = 10;
  else if (base < 2 || base > 36) {
    cp_errno = CPE_INVALID;
    return begin;
  }

  if (s >= end || *s == '_')
    return begin;

  uint32_t overflow_val = 0xFFFFFFFFU / base;
  int32_t overflow_digit = 0xFFFFFFFFU - (overflow_val * base);

  uint32_t val = 0;
  cp_errno = CPE_FORMAT;

  while (s < end) {

    int digit;
    if (*s >= '0' && *s <= '9')
      digit = *s - '0';
    else if (base > 10 && *s >= 'A' && *s <= 'Z')
      digit = *s - 'A' + 10;
    else if (base > 10 && *s >= 'a' && *s <= 'z')
      digit = *s - 'a' + 10;
    else if (*s == '_' && s + 1 < end && s[1] != '_')

      goto next_digit;
    else
      digit = 36;
    if (digit >= base)
      break;
    else if (val == 0 && cp_errno == CPE_FORMAT)
      cp_errno = CPE_OK;

    if (val > overflow_val || (val == overflow_val && digit > overflow_digit))
      cp_errno = CPE_OVERFLOW;

    val = val * base + digit;
   next_digit:
    s++;
  }

  if (cp_errno == CPE_FORMAT)
    return begin;
  else {
    *result = (cp_errno ? 0xFFFFFFFFU : val);
    return (s > begin && s[-1] == '_' ? s - 1 : s);
  }
}
