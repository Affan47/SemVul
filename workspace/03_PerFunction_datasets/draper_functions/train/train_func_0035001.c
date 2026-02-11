output_uleb128 (char *p, valueT value)
{
  char *orig = p;

  do
    {
      unsigned byte = (value & 0x7f);
      value >>= 7;
      if (value != 0)

	byte |= 0x80;

      *p++ = byte;
    }
  while (value != 0);

  return p - orig;
}
