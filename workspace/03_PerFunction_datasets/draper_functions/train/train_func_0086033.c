mve_quantize (const GstMveMux * mve, const guint16 * src,
    guint w, guint h, guint n, guint ncols, guint16 * scratch, guint16 * cols)
{
  guint x, y, i;
  GstMveQuant q[4];
  const guint16 *data;
  guint16 *dest;
  guint32 error;

  g_assert (n <= 4 && ncols <= 4);

  src += ((n * w) % 8) + (((n * (8 - h)) / (12 - w)) * h * mve->width);
  scratch += ((n * w) % 8) + (((n * (8 - h)) / (12 - w)) * h * 8);

  mve_quant_init (mve, q, ncols, src, w, h);

  do {
    data = src;
    dest = scratch;
    error = 0;


    for (y = 0; y < h; ++y) {
      for (x = 0; x < w; ++x) {
        guint16 c = data[x];
        guint8 r = MVE_RVAL (c), g = MVE_GVAL (c), b = MVE_BVAL (c);
        guint32 minerr = MVE_APPROX_MAX_ERROR, err;
        GstMveQuant *best = NULL;

        for (i = 0; i < ncols; ++i) {
          err = mve_color_dist_rgb (r, g, b, q[i].r, q[i].g, q[i].b);

          if (err < minerr) {
            minerr = err;
            best = &q[i];
          }
        }

        if (G_UNLIKELY (!best))
          continue;

        ++best->hits;
        best->r_total += r;
        best->g_total += g;
        best->b_total += b;

        if (minerr > best->max_error) {
          best->max_error = minerr;
          best->max_miss = c;
        }

        error += minerr;
        dest[x] = best->col;
      }
      data += mve->width;
      dest += 8;
    }
  } while (mve_quant_update_clusters (q, ncols));


  for (i = 0; i < ncols; ++i)
    cols[i] = q[i].col;

  return error;
}
