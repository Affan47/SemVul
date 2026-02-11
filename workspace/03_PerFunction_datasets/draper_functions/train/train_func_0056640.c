vs_image_scale_4tap_AYUV64 (const VSImage * dest, const VSImage * src,
    uint8_t * tmpbuf8)
{
  int yacc;
  int y_increment;
  int x_increment;
  int i;
  int j;
  int xacc;
  int k;
  guint16 *tmpbuf = (guint16 *) tmpbuf8;

  int dest_pixstride = dest->stride / sizeof (guint16);

  if (dest->height == 1)
    y_increment = 0;
  else
    y_increment = ((src->height - 1) << 16) / (dest->height - 1);

  if (dest->width == 1)
    x_increment = 0;
  else
    x_increment = ((src->width - 1) << 16) / (dest->width - 1);

  k = 0;
  for (i = 0; i < 4; i++) {
    xacc = 0;
    vs_scanline_resample_4tap_AYUV64 (tmpbuf + i * dest_pixstride,
        (guint16 *) (src->pixels + CLAMP (i, 0, src->height - 1) * src->stride),
        dest->width, src->width, &xacc, x_increment);
  }

  yacc = 0;
  for (i = 0; i < dest->height; i++) {
    uint16_t *t0, *t1, *t2, *t3;

    j = yacc >> 16;

    while (j > k) {
      k++;
      if (k + 3 < src->height) {
        xacc = 0;
        vs_scanline_resample_4tap_AYUV64 (tmpbuf + ((k +
                    3) & 3) * dest_pixstride,
            (guint16 *) (src->pixels + (k + 3) * src->stride), dest->width,
            src->width, &xacc, x_increment);
      }
    }

    t0 = tmpbuf + (CLAMP (j - 1, 0, src->height - 1) & 3) * dest_pixstride;
    t1 = tmpbuf + (CLAMP (j, 0, src->height - 1) & 3) * dest_pixstride;
    t2 = tmpbuf + (CLAMP (j + 1, 0, src->height - 1) & 3) * dest_pixstride;
    t3 = tmpbuf + (CLAMP (j + 2, 0, src->height - 1) & 3) * dest_pixstride;
    vs_scanline_merge_4tap_AYUV64 ((guint16 *) (dest->pixels +
            i * dest->stride), t0, t1, t2, t3, dest->width, yacc & 0xffff);

    yacc += y_increment;
  }
}
