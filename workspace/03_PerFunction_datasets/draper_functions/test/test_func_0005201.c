line10_copy (guint8 * dest, guint8 * src, int n)
{
  int i;
  guint32 a;
  for (i = 0; i < n; i++) {
    a = get_word10 (src);
    GST_WRITE_UINT32_BE (dest, a);
    src += 5;
    dest += 4;
  }

}
