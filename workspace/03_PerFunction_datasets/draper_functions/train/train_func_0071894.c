fmt_convert(GPixmap *pm, const ddjvu_format_t *fmt, char *buffer, int rowsize)
{
  int w = pm->columns();
  int h = pm->rows();

  if (fmt->rtoptobottom)
    {
      for(int r=h-1; r>=0; r--, buffer+=rowsize)
        fmt_convert_row((*pm)[r], w, fmt, buffer);
    }
  else
    {
      for(int r=0; r<h; r++, buffer+=rowsize)
        fmt_convert_row((*pm)[r], w, fmt, buffer);
    }
}
