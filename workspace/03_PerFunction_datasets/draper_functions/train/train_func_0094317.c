XSetCropGeometry(Display *display,XWindows *windows,
  RectangleInfo *crop_info,Image *image)
{
  char
    text[MaxTextExtent];

  int
    x,
    y;

  MagickRealType
    scale_factor;

  unsigned int
    height,
    width;

  if (windows->info.mapped != MagickFalse)
    {


      (void) FormatLocaleString(text,MaxTextExtent," %.20gx%.20g%+.20g%+.20g",
        (double) crop_info->width,(double) crop_info->height,(double)
        crop_info->x,(double) crop_info->y);
      XInfoWidget(display,windows,text);
    }


  x=0;
  y=0;
  width=(unsigned int) image->columns;
  height=(unsigned int) image->rows;
  if (windows->image.crop_geometry != (char *) NULL)
    (void) XParseGeometry(windows->image.crop_geometry,&x,&y,&width,&height);
  else
    windows->image.crop_geometry=AcquireString((char *) NULL);


  scale_factor=(MagickRealType) width/windows->image.ximage->width;
  if (crop_info->x > 0)
    x+=(int) (scale_factor*crop_info->x+0.5);
  width=(unsigned int) (scale_factor*crop_info->width+0.5);
  if (width == 0)
    width=1;
  scale_factor=(MagickRealType) height/windows->image.ximage->height;
  if (crop_info->y > 0)
    y+=(int) (scale_factor*crop_info->y+0.5);
  height=(unsigned int) (scale_factor*crop_info->height+0.5);
  if (height == 0)
    height=1;
  (void) FormatLocaleString(windows->image.crop_geometry,MaxTextExtent,
    "%ux%u%+d%+d",width,height,x,y);
}
