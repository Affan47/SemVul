gs_make_image(gs)
gifState *gs;
{
  Image *image;
  int i;
  bool gray = true;

  if (gs->l_cmap_flag)
  {
    image = newRGBImage(gs->img_width, gs->img_height, gs->l_pixel_bits);
    if (!image) return(GS_ERR_NOMEM);

    image->rgb.red = gs->l_cmap[GIF_RED];
    image->rgb.green = gs->l_cmap[GIF_GRN];
    image->rgb.blue = gs->l_cmap[GIF_BLU];
    image->rgb.used = gs->l_ncolors;
  }
  else
  {
    image = newRGBImage(gs->img_width, gs->img_height, gs->g_pixel_bits);
    if (!image) return(GS_ERR_NOMEM);

    image->rgb.red = gs->g_cmap[GIF_RED];
    image->rgb.green = gs->g_cmap[GIF_GRN];
    image->rgb.blue = gs->g_cmap[GIF_BLU];
    image->rgb.used = gs->g_ncolors;
  }

  for(i = 0; i < image->rgb.used; i++)
    if(image->rgb.red[i] >> 8 != image->rgb.green[i] >> 8 ||
       image->rgb.red[i] >> 8 != image->rgb.blue[i] >> 8)
    {
      gray = false;
      break;
    }
  if(gray) image->type = IGRAY;

  image->transparent = gs->transparent;
  gs->image = image;
  gs->state = GS_DECODE_DATA;
  image->x = 0;
  image->pass = 0;
  if (gs->interlace_flag) image->y = interlace_start[image->pass];
  else image->y = 0;

  return(GS_SUCCESS);
}
