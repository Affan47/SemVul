putline_v216 (GstBlendVideoFormatInfo * dest, GstBlendVideoFormatInfo * srcinfo,
    const guint8 * line, guint xoff, int j)
{
  int i;
  guint8 *destline = GET_LINE (dest, 0, j) + GST_ROUND_UP_2 (xoff + 3);

  for (i = 0; i < srcinfo->width / 2; i++) {
    GST_WRITE_UINT16_LE (destline + i * 8 + 0, line[(i * 2 + 0) * 4 + 2] << 8);
    GST_WRITE_UINT16_LE (destline + i * 8 + 2, line[(i * 2 + 0) * 4 + 1] << 8);
    GST_WRITE_UINT16_LE (destline + i * 8 + 4, line[(i * 2 + 1) * 4 + 3] << 8);
    GST_WRITE_UINT16_LE (destline + i * 8 + 8, line[(i * 2 + 0) * 4 + 1] << 8);
  }
}
