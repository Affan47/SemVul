is_number (const struct token *tp)
{
  const char *str = tp->chars;
  int len = tp->charcount;
  int radix = 10;
  enum { unknown, exact, inexact } exactness = unknown;
  bool seen_radix_prefix = false;
  bool seen_exactness_prefix = false;

  if (len == 1)
    if (*str == '+' || *str == '-')
      return false;
  while (len >= 2 && *str == '#')
    {
      switch (str[1])
        {
        case 'B': case 'b':
          if (seen_radix_prefix)
            return false;
          radix = 2;
          seen_radix_prefix = true;
          break;
        case 'O': case 'o':
          if (seen_radix_prefix)
            return false;
          radix = 8;
          seen_radix_prefix = true;
          break;
        case 'D': case 'd':
          if (seen_radix_prefix)
            return false;
          radix = 10;
          seen_radix_prefix = true;
          break;
        case 'X': case 'x':
          if (seen_radix_prefix)
            return false;
          radix = 16;
          seen_radix_prefix = true;
          break;
        case 'E': case 'e':
          if (seen_exactness_prefix)
            return false;
          exactness = exact;
          seen_exactness_prefix = true;
          break;
        case 'I': case 'i':
          if (seen_exactness_prefix)
            return false;
          exactness = inexact;
          seen_exactness_prefix = true;
          break;
        default:
          return false;
        }
      str += 2;
      len -= 2;
    }
  if (exactness != inexact)
    {

      if (is_integer_syntax (str, len, 10))
        return true;


    }
  if (exactness != exact)
    {

      if (is_other_number_syntax (str, len, 10, true))
        return true;
    }
  return false;
}
