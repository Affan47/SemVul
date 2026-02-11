vs_image_scale_lanczos_AYUV_int32 (const VSImage * dest, const VSImage * src,
    uint8_t * tmpbuf, double sharpness, gboolean dither, double a,
    double sharpen)
{
  Scale s = { 0 };
  Scale *scale = &s;
  int n_taps;

  scale->dest = dest;
  scale->src = src;

  n_taps = scale1d_get_n_taps (src->width, dest->width, a, sharpness);
  n_taps = ROUND_UP_4 (n_taps);
  scale1d_calculate_taps_int32 (&scale->x_scale1d,
      src->width, dest->width, n_taps, a, sharpness, sharpen, S32_SHIFT1);

  n_taps = scale1d_get_n_taps (src->height, dest->height, a, sharpness);
  scale1d_calculate_taps_int32 (&scale->y_scale1d,
      src->height, dest->height, n_taps, a, sharpness, sharpen, S32_SHIFT2);

  scale->dither = dither;

  switch (scale->x_scale1d.n_taps) {
    case 4:
      scale->horiz_resample_func =
          (HorizResampleFunc) resample_horiz_int32_int32_ayuv_taps4_shift0;
      break;
    case 8:
      scale->horiz_resample_func =
          (HorizResampleFunc) resample_horiz_int32_int32_ayuv_taps8_shift0;
      break;
    case 12:
      scale->horiz_resample_func =
          (HorizResampleFunc) resample_horiz_int32_int32_ayuv_taps12_shift0;
      break;
    case 16:
      scale->horiz_resample_func =
          (HorizResampleFunc) resample_horiz_int32_int32_ayuv_taps16_shift0;
      break;
    default:
      scale->horiz_resample_func =
          (HorizResampleFunc) resample_horiz_int32_int32_ayuv_generic;
      break;
  }

  scale->tmpdata =
      g_malloc (sizeof (int32_t) * scale->dest->width * scale->src->height * 4);

  vs_scale_lanczos_AYUV_int32 (scale);

  scale1d_cleanup (&scale->x_scale1d);
  scale1d_cleanup (&scale->y_scale1d);
  g_free (scale->tmpdata);
}
