conv_gaF_gF (unsigned char *src, unsigned char *dst, long samples)
{
  long n = samples;

  while (n--)
    {
      *(int *) dst = (*(int *) src);
      dst         += 4;
      src         += 4;
      src         += 4;
    }
  return samples;
}
