deallocate_colors(Gif_XColormap *gfxc)
{
  Gif_XContext *gfx = gfxc->x_context;
  if (gfxc->allocated && !gfxc->claimed) {
    XFreeColors(gfx->display, gfx->colormap, gfxc->pixels, gfxc->npixels, 0);
    gfxc->allocated = 0;
  }
}
