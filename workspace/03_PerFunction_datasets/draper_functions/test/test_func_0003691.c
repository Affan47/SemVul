rgbe_apply_exponent (const rgbe_file *file,
                     gfloat          *rgb,
                     gfloat           e)
{
  gfloat mult;

  g_return_if_fail (file);
  g_return_if_fail (rgb);

  if (e == 0)
    {
      rgb[OFFSET_R] = rgb[OFFSET_G] = rgb[OFFSET_B] = 0;
      goto cleanup;
    }

  mult = ldexp (1.0, e - (128 + 8));
  rgb[OFFSET_R] *= mult                  *
                   file->header.exposure *
                   file->header.colorcorr[OFFSET_R];
  rgb[OFFSET_G] *= mult                  *
                   file->header.exposure *
                   file->header.colorcorr[OFFSET_G];
  rgb[OFFSET_B] *= mult                  *
                   file->header.exposure *
                   file->header.colorcorr[OFFSET_B];
  rgb[OFFSET_A]  = 1.0f;

cleanup:
  return;
}
