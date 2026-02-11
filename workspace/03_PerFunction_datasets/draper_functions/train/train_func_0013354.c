deinterlace_c (guint8 * dst, const guint8 * lum_m4, const guint8 * lum_m3,
    const guint8 * lum_m2, const guint8 * lum_m1, const guint8 * lum, gint size)
{
  if (lum_m2 == NULL) {
    deinterlace_line_linear (dst, lum_m1, lum_m3, size);
  } else {
    deinterlace_line_vfir (dst, lum_m4, lum_m3, lum_m2, lum_m1, lum, size);
  }
}
