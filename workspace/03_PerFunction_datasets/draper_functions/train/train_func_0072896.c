number_to_chars_littleendian (char *buf, valueT val, int n)
{
  if (n <= 0)
    abort ();
  while (n--)
    {
      *buf++ = val & 0xff;
      val >>= 8;
    }
}
