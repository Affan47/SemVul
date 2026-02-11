upsample(const GPixmap *src, int factor, const GRect *pdr)
{

  GRect rect(0, 0, src->columns()*factor, src->rows()*factor);
  if (pdr != 0)
  {
    if (pdr->xmin < rect.xmin ||
        pdr->ymin < rect.ymin ||
        pdr->xmax > rect.xmax ||
        pdr->ymax > rect.ymax  )
      G_THROW( ERR_MSG("GPixmap.overflow2") );
    rect = *pdr;
  }

  init(rect.height(), rect.width(), 0);

  int sy, sy1, sxz, sx1z;
  euclidian_ratio(rect.ymin, factor, sy, sy1);
  euclidian_ratio(rect.xmin, factor, sxz, sx1z);

  const GPixel *sptr = (*src)[sy];
  GPixel *dptr = (*this)[0];
  for (int y=0; y<nrows; y++)
  {

    int sx = sxz;
    int sx1 = sx1z;
    for (int x=0; x<ncolumns; x++)
    {
      dptr[x] = sptr[sx];

      if (++sx1 >= factor)
      {
        sx1 = 0;
        sx += 1;
      }
    }

    dptr += rowsize();
    if (++sy1 >= factor)
    {
      sy1 = 0;
      sptr += src->rowsize();
    }
  }
}
