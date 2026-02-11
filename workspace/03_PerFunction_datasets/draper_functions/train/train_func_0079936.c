pack_v216 (const GstVideoFormatInfo * info, GstVideoPackFlags flags,
    const gpointer src, gint sstride, gpointer data[GST_VIDEO_MAX_PLANES],
    const gint stride[GST_VIDEO_MAX_PLANES], GstVideoChromaSite chroma_site,
    gint y, gint width)
{
  int i;
  guint8 *d = GET_LINE (y);
  const guint16 *s = src;

  for (i = 0; i < width - 1; i += 2) {
    GST_WRITE_UINT16_LE (d + i * 4 + 0, s[(i + 0) * 4 + 2]);
    GST_WRITE_UINT16_LE (d + i * 4 + 2, s[(i + 0) * 4 + 1]);
    GST_WRITE_UINT16_LE (d + i * 4 + 4, s[(i + 0) * 4 + 3]);
    GST_WRITE_UINT16_LE (d + i * 4 + 6, s[(i + 1) * 4 + 1]);
  }
  if (i == width - 1) {
    GST_WRITE_UINT16_LE (d + i * 4 + 0, s[i * 4 + 2]);
    GST_WRITE_UINT16_LE (d + i * 4 + 2, s[i * 4 + 1]);
    GST_WRITE_UINT16_LE (d + i * 4 + 4, s[i * 4 + 3]);
    GST_WRITE_UINT16_LE (d + i * 4 + 6, s[i * 4 + 1]);
  }
}
