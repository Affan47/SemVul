conv_rgbaF_rgb8 (unsigned char *src, unsigned char *dst, long samples)
{
  long n = samples;

  while (n--)
    {
      int c;

      for (c = 0; c < 3; c++)
        {
          *(unsigned char *) dst = (*(float *) src) * 255.0;
          dst                   += 1;
          src                   += 4;
        }
      src += 4;
    }
  return samples;
}
