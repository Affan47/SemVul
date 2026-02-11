apply_background(Gif_XContext *gfx, Gif_Stream *gfs, int i, Pixmap pixmap)
{
  Gif_Image *gfi = gfs->images[i >= 0 ? i : 0];
  Gif_Colormap *gfcm = (gfi->local ? gfi->local : gfs->global);
  unsigned long bg_pixel;


  if (gfs->global && gfs->background < gfs->global->ncol
      && gfs->images[0]->transparent < 0) {
    Gif_XColormap *gfxc = find_x_colormap_extension(gfx, gfcm, 1);
    if (!gfxc)
      return -1;
    allocate_colors(gfxc);
    bg_pixel = gfxc->pixels[gfs->background];
  } else
    bg_pixel = gfx->transparent_pixel;


  if (!gfx->image_gc)
    gfx->image_gc = XCreateGC(gfx->display, pixmap, 0, 0);
  if (!gfx->image_gc)
    return -1;
  XSetForeground(gfx->display, gfx->image_gc, bg_pixel);
  gfx->transparent_pixel = bg_pixel;


  if (i < 0)
    XFillRectangle(gfx->display, pixmap, gfx->image_gc,
		   0, 0, gfs->screen_width, gfs->screen_height);
  else
    XFillRectangle(gfx->display, pixmap, gfx->image_gc,
		   gfi->left, gfi->top, gfi->width, gfi->height);


  return 0;
}
