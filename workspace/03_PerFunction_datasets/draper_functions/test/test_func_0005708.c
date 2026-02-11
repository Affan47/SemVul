chroma_keying_yuv (gint a, gint * y, gint * u,
    gint * v, gint cr, gint cb, gint smin, gint smax, guint8 accept_angle_tg,
    guint8 accept_angle_ctg, guint8 one_over_kc, guint8 kfgy_scale, gint8 kg,
    guint noise_level2)
{
  gint tmp, tmp1;
  gint x1, y1;
  gint x, z;
  gint b_alpha;


  if (*y < smin || *y > smax)
    return a;


  tmp = ((*u) * cb + (*v) * cr) >> 7;
  x = CLAMP (tmp, -128, 127);
  tmp = ((*v) * cb - (*u) * cr) >> 7;
  z = CLAMP (tmp, -128, 127);


  tmp = (x * accept_angle_tg) >> 4;
  tmp = MIN (tmp, 127);

  if (abs (z) > tmp) {

    return a;
  }


  tmp = (z * accept_angle_ctg) >> 4;
  tmp = CLAMP (tmp, -128, 127);
  x1 = abs (tmp);
  y1 = z;

  tmp1 = x - x1;
  tmp1 = MAX (tmp1, 0);
  b_alpha = (tmp1 * one_over_kc) / 2;
  b_alpha = 255 - CLAMP (b_alpha, 0, 255);
  b_alpha = (a * b_alpha) >> 8;

  tmp = (tmp1 * kfgy_scale) >> 4;
  tmp1 = MIN (tmp, 255);

  *y = (*y < tmp1) ? 0 : *y - tmp1;


  tmp = (x1 * cb - y1 * cr) >> 7;
  *u = CLAMP (tmp, -128, 127);

  tmp = (x1 * cr + y1 * cb) >> 7;
  *v = CLAMP (tmp, -128, 127);


  tmp = z * z + (x - kg) * (x - kg);
  tmp = MIN (tmp, 0xffff);

  if (tmp < noise_level2)
    b_alpha = 0;

  return b_alpha;
}
