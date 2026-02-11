conv_gaF_rgbaF (unsigned char *src, unsigned char *dst, long samples)
{
  long n = samples;

  while (n--)
    {
      int c;

      for (c = 0; c < 3; c++)
        {
          (*(int *) dst) = (*(int *) src);
          dst           += 4;
        }
      src           += 4;
      (*(int *) dst) = (*(int *) src);
      dst           += 4;
      src           += 4;
    }
  return samples;
}
