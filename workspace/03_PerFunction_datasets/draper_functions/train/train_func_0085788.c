conv_gF_rgbF (unsigned char *src, unsigned char *dst, long samples)
{
  long n = samples;

  while (n--)
    {
      int c;

      for (c = 0; c < 3; c++)
        {
          (*(float *) dst) = (*(float *) src);
          dst             += 4;
        }
      src += 4;
    }
  return samples;
}
