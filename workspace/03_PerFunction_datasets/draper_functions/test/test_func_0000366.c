conv_rgbaF_rgb8 (unsigned char *src, unsigned char *dst, long samples)
{
  long n = samples;

  while (n--)
    {
      register float f = (*(float *) src);
      *(unsigned char *) dst = table_F_8[gggl_float_to_index16 (f)];
      src                   += 4;
      dst                   += 1;

      f                      = (*(float *) src);
      *(unsigned char *) dst = table_F_8[gggl_float_to_index16 (f)];
      src                   += 4;
      dst                   += 1;

      f                      = (*(float *) src);
      *(unsigned char *) dst = table_F_8[gggl_float_to_index16 (f)];
      src                   += 4;
      dst                   += 1;

      src += 4;
    }
  return samples;
}
