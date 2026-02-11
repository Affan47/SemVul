insert_double (double_int val, unsigned char *dest)
{
  unsigned char *p0 = dest;
  unsigned char *p1 = dest + sizeof (HOST_WIDE_INT);

  if (WORDS_BIG_ENDIAN)
    {
      p0 = p1;
      p1 = dest;
    }

  insert_int ((HOST_WIDE_INT) val.low, sizeof (HOST_WIDE_INT), p0);
  insert_int ((HOST_WIDE_INT) val.high, sizeof (HOST_WIDE_INT), p1);
}
