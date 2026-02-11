stpi_unpack_2_1(int length,
		const unsigned char *in,
		unsigned char **outs)
{
  unsigned char	tempin, bit, temp0, temp1;

  if (length <= 0)
    return;
  for (bit = 128, temp0 = 0, temp1 = 0;
       length > 0;
       length --)
    {
      tempin = *in++;

      if (tempin & 128)
        temp0 |= bit;
      if (tempin & 64)
        temp1 |= bit;
      bit >>= 1;
      if (tempin & 32)
        temp0 |= bit;
      if (tempin & 16)
        temp1 |= bit;
      bit >>= 1;
      if (tempin & 8)
        temp0 |= bit;
      if (tempin & 4)
        temp1 |= bit;
      bit >>= 1;
      if (tempin & 2)
        temp0 |= bit;
      if (tempin & 1)
        temp1 |= bit;

      if (bit > 1)
        bit >>= 1;
      else
      {
        bit     = 128;
	*outs[0]++ = temp0;
	*outs[1]++ = temp1;

	temp0   = 0;
	temp1   = 0;
      }
    }

  if (bit < 128)
    {
      *outs[0]++ = temp0;
      *outs[1]++ = temp1;
    }
}
