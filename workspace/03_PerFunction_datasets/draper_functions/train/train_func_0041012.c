mve_encode_0xc (GstMveEncoderData * enc, const guint8 * src, GstMveApprox * apx)
{

  guint i = 0, x, y;
  const guint w = enc->mve->width;
  guint16 r, g, b;


  for (y = 0; y < 4; ++y) {
    for (x = 0; x < 4; ++x) {
      guint32 p = enc->palette[src[0]];

      r = MVE_RVAL (p) + 2;
      g = MVE_GVAL (p) + 2;
      b = MVE_BVAL (p) + 2;

      p = enc->palette[src[1]];
      r += MVE_RVAL (p);
      g += MVE_GVAL (p);
      b += MVE_BVAL (p);

      p = enc->palette[src[w]];
      r += MVE_RVAL (p);
      g += MVE_GVAL (p);
      b += MVE_BVAL (p);

      p = enc->palette[src[w + 1]];
      r += MVE_RVAL (p);
      g += MVE_GVAL (p);
      b += MVE_BVAL (p);

      apx->block[i] = apx->block[i + 1] = apx->block[i + 2] =
          apx->block[i + 3] = apx->data[i >> 2] =
          mve_find_pal_color (enc->palette, MVE_COL (r >> 2, g >> 2, b >> 2));

      i += 4;
      src += 2;
    }
    src += (w * 2) - 8;
  }

  apx->error = mve_block_error_packed (enc, src - (8 * w), apx->block);
  return apx->error;
}
