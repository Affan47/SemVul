getline16_convert (ColorspaceConvert * convert, guint16 * dest,
    const guint8 * src, int j)
{
  int i;
  convert->getline (convert, convert->tmpline, src, j);
  for (i = 0; i < convert->width * 4; i++) {
    dest[i] = convert->tmpline[i] << 8;
  }
}
