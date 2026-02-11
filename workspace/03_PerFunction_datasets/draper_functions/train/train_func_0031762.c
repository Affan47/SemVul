hwint_to_ascii (unsigned HOST_WIDE_INT number, const unsigned int base,
		char *buffer, const unsigned int min_digits)
{
  static const char base_digits[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  unsigned digits = 0;

  while (number)
    {
      unsigned HOST_WIDE_INT d = number / base;

      *--buffer = base_digits[number - d * base];
      digits++;
      number = d;
    }
  while (digits < min_digits)
    {
      *--buffer = base_digits[0];
      digits++;
    }
  return digits;
}
