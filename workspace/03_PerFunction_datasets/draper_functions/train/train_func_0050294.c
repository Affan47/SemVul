convert_hline_bayer (paintinfo * p, int y)
{
  int i;
  guint8 *R = p->yp + y * p->ystride;
  guint8 *argb = p->tmpline;
  int x_inv = p->bayer_x_invert;
  int y_inv = p->bayer_y_invert;

  if ((y ^ y_inv) & 1) {
    for (i = 0; i < p->width; i++) {
      if ((i ^ x_inv) & 1) {
        R[i] = argb[4 * i + 1];
      } else {
        R[i] = argb[4 * i + 2];
      }
    }
  } else {
    for (i = 0; i < p->width; i++) {
      if ((i ^ x_inv) & 1) {
        R[i] = argb[4 * i + 2];
      } else {
        R[i] = argb[4 * i + 3];
      }
    }
  }
}
