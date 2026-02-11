parse_quant (GstBitReader * br, guint8 quant_mat[64],
    const guint8 default_quant_mat[64], guint8 * load_quant_mat)
{
  READ_UINT8 (br, *load_quant_mat, 1);
  if (*load_quant_mat) {
    guint i;
    guint8 val;

    val = 1;
    for (i = 0; i < 64; i++) {

      if (val != 0)
        READ_UINT8 (br, val, 8);

      if (val == 0) {
        if (i == 0)
          goto invalid_quant_mat;
        quant_mat[mpeg4_zigzag_8x8[i]] = quant_mat[mpeg4_zigzag_8x8[i - 1]];
      } else
        quant_mat[mpeg4_zigzag_8x8[i]] = val;
    }
  } else
    memcpy (quant_mat, default_quant_mat, 64);

  return TRUE;

failed:
  GST_WARNING ("failed parsing quant matrix");
  return FALSE;

invalid_quant_mat:
  GST_WARNING ("the first value should be non zero");
  goto failed;
}
