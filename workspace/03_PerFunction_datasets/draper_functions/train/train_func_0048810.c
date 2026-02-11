init(const GBitmap &ref, const GRect &rect, int border)
{
  GMonitorLock lock(monitor());

  if (this == &ref)
    {
      GBitmap tmp;
      tmp.grays = grays;
      tmp.border = border;
      tmp.bytes_per_row = bytes_per_row;
      tmp.ncolumns = ncolumns;
      tmp.nrows = nrows;
      tmp.bytes = bytes;
      tmp.gbytes_data.swap(gbytes_data);
      tmp.grle.swap(grle);
      bytes = 0 ;
      init(tmp, rect, border);
    }
  else
    {
      GMonitorLock lock(ref.monitor());

      init(rect.height(), rect.width(), border);
      grays = ref.grays;

      GRect rect2(0, 0, ref.columns(), ref.rows() );
      rect2.intersect(rect2, rect);
      rect2.translate(-rect.xmin, -rect.ymin);

      if (! rect2.isempty())
        {
          for (int y=rect2.ymin; y<rect2.ymax; y++)
            {
              unsigned char *dst = (*this)[y];
              const unsigned char *src = ref[y+rect.ymin] + rect.xmin;
              for (int x=rect2.xmin; x<rect2.xmax; x++)
                dst[x] = src[x];
            }
        }
    }
}
