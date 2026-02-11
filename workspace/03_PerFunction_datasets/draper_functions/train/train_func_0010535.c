mve_block_error_packed (const GstMveMux * mve, const guint16 * block,
    const guint16 * scratch)
{

  guint32 e = 0;
  guint x, y;

  for (y = 0; y < 8; ++y) {
    for (x = 0; x < 8; ++x) {
      e += mve_color_dist (block[x], scratch[x]);
    }
    block += mve->width;
    scratch += 8;
  }

  return e;
}
