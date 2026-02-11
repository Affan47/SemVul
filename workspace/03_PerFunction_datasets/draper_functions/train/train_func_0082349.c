pack_410 (const GstVideoFormatInfo * info, GstVideoPackFlags flags,
    const gpointer src, gint sstride, gpointer data[GST_VIDEO_MAX_PLANES],
    const gint stride[GST_VIDEO_MAX_PLANES], GstVideoChromaSite chroma_site,
    gint y, gint width)
{
  int i;
  gint uv = GET_UV_410 (y, flags);
  guint8 *destY = GET_Y_LINE (y);
  guint8 *destU = GET_U_LINE (uv);
  guint8 *destV = GET_V_LINE (uv);
  const guint8 *s = src;

  for (i = 0; i < width - 3; i += 4) {
    destY[i] = s[i * 4 + 1];
    destY[i + 1] = s[i * 4 + 5];
    destY[i + 2] = s[i * 4 + 9];
    destY[i + 3] = s[i * 4 + 13];
    if (y % 4 == 0) {
      destU[i >> 2] = s[i * 4 + 2];
      destV[i >> 2] = s[i * 4 + 3];
    }
  }
  if (i < width) {
    destY[i] = s[i * 4 + 1];
    if (y % 4 == 0) {
      destU[i >> 2] = s[i * 4 + 2];
      destV[i >> 2] = s[i * 4 + 3];
    }
    if (i < width - 1)
      destY[i + 1] = s[i * 4 + 5];
    if (i < width - 2)
      destY[i + 2] = s[i * 4 + 9];
  }
}
