pack_GRAY16_LE (const GstVideoFormatInfo * info, GstVideoPackFlags flags,
    const gpointer src, gint sstride, gpointer data[GST_VIDEO_MAX_PLANES],
    const gint stride[GST_VIDEO_MAX_PLANES], GstVideoChromaSite chroma_site,
    gint y, gint width)
{
  int i;
  guint16 *d = GET_LINE (y);
  const guint16 *s = src;

  for (i = 0; i < width; i++) {
    GST_WRITE_UINT16_LE (d + i, s[i * 4 + 1]);
  }
}
