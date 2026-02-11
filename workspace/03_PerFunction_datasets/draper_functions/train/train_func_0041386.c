conv_rgbaF_rgb16 (unsigned char *src, unsigned char *dst, long samples)
{
  long n = samples;

  while (n--)
    {
      int c;

      for (c = 0; c < 3; c++)
        {
          *(unsigned short *) dst = (*(float *) src) * 65535.0;
          dst                    += 2;
          src                    += 4;
        }
      src += 4;
    }
  return samples;
}
