bfd_get_bits (addr, bits, big_p)
     bfd_byte *addr;
     int bits;
     bfd_boolean big_p;
{
  bfd_vma data;
  int i;
  int bytes;

  if (bits % 8 != 0)
    abort ();

  data = 0;
  bytes = bits / 8;
  for (i = 0; i < bytes; i++)
    {
      int index = big_p ? i : bytes - i - 1;

      data = (data << 8) | addr[index];
    }

  return data;
}
