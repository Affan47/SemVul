apply_image(Gif_XContext *gfx, Gif_Stream *gfs, Gif_Image *gfi, Pixmap pixmap)
{
  Pixmap image = Gif_XImage(gfx, gfs, gfi), mask;
  if (image == None)
    return -1;

  if (gfi->transparent >= 0) {
    mask = Gif_XMask(gfx, gfs, gfi);
    if (mask == None) {
      XFreePixmap(gfx->display, image);
      return -1;
    }

    XSetClipMask(gfx->display, gfx->image_gc, mask);
    XSetClipOrigin(gfx->display, gfx->image_gc, gfi->left, gfi->top);
    XCopyArea(gfx->display, image, pixmap, gfx->image_gc,
	      0, 0, gfi->width, gfi->height, gfi->left, gfi->top);
    XSetClipMask(gfx->display, gfx->image_gc, None);
    XFreePixmap(gfx->display, mask);
  } else {
    XCopyArea(gfx->display, image, pixmap, gfx->image_gc,
	      0, 0, gfi->width, gfi->height, gfi->left, gfi->top);
  }

  XFreePixmap(gfx->display, image);
  return 0;
}
