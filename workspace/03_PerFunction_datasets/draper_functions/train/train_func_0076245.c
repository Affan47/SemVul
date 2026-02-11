get_bg_red(GP<DjVuImage> dimg)
{
  GP<GPixmap> pm = 0;

  int width = dimg->get_width();
  int height = dimg->get_height();
  if (width<=0 || height<=0) return 0;

  GP<IW44Image> bg44 = dimg->get_bg44();
  if (bg44)
    {
      int w = bg44->get_width();
      int h = bg44->get_height();

      if (w==0 || h==0 || width==0 || height==0)
        return 0;
      return compute_red(width,height,w,h);
    }

  GP<GPixmap>  bgpm = dimg->get_bgpm();
  if (bgpm)
    {
      int w = bgpm->columns();
      int h = bgpm->rows();

      if (w==0 || h==0 || width==0 || height==0)
        return 0;
      return compute_red(width,height,w,h);
    }
  return 0;
}
