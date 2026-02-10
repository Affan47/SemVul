convert_double_u32_scaled (double   min_val,
                           double   max_val,
                           uint32_t min,
                           uint32_t max,
                           char    *src,
                           char    *dst,
                           int      src_pitch,
                           int      dst_pitch,
                           long     n)
{
  while (n--)
    {
      double   dval = *(double *) src;
      uint32_t u32val;

      if (dval < min_val)
        u32val = min;
      else if (dval > max_val)
        u32val = max;
      else
        u32val = rint ((dval - min_val) / (max_val - min_val) * (max - min) + min);

      *(uint32_t *) dst = u32val;
      dst              += dst_pitch;
      src              += src_pitch;
    }
  return n;
}
