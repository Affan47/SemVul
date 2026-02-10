putline_r210 (ColorspaceConvert * convert, guint8 * dest, const guint8 * src,
    int j)
{
  int i;
  guint8 *destline = FRAME_GET_LINE (dest, 0, j);
  for (i = 0; i < convert->width / 2; i++) {
    guint32 x = 0;
    x |= src[i * 4 + 1] << 22;
    x |= (src[i * 4 + 1] & 0xc0) << 14;
    x |= src[i * 4 + 2] << 12;
    x |= (src[i * 4 + 2] & 0xc0) << 10;
    x |= src[i * 4 + 3] << 2;
    x |= (src[i * 4 + 3] & 0xc0) >> 6;
    GST_WRITE_UINT32_BE (destline + i * 4, x);
  }
}
