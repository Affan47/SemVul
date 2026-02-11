mbe_7100x4400hamming1511 (char *in, char *out)
{
  int i, j, errs, block, syndrome, stmp, stmp2;

  errs = 0;

  block = 0;
  for (i = 14; i >= 0; i--)
    {
      block <<= 1;
      block |= in[i];
    }

  syndrome = 0;
  for (i = 0; i < 4; i++)
    {
      syndrome <<= 1;
      stmp = block;
      stmp &= imbe7100x4400hammingGenerator[i];

      stmp2 = (stmp % 2);
      for (j = 0; j < 14; j++)
        {
          stmp >>= 1;
          stmp2 ^= (stmp % 2);
        }

      syndrome |= stmp2;
    }
  if (syndrome > 0)
    {
      errs++;
      block ^= hammingMatrix[syndrome];
    }

  for (i = 14; i >= 0; i--)
    {
      out[i] = (block & 0x4000) >> 14;
      block = block << 1;
    }
  return (errs);
}
