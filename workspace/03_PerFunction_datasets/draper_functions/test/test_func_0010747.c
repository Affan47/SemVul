put_image_in_screen(Gif_Stream *gfs, Gif_Image *gfi, uint16_t *screen)
{
  int transparent = gfi->transparent;
  int x, y;
  int w = gfi->width;
  int h = gfi->height;
  if (gfi->left + w > gfs->screen_width)
      w = gfs->screen_width - gfi->left;
  if (gfi->top + h > gfs->screen_height)
      h = gfs->screen_height - gfi->top;

  for (y = 0; y < h; y++) {
    uint16_t *move = screen + gfs->screen_width * (y + gfi->top) + gfi->left;
    uint8_t *line = gfi->img[y];
    for (x = 0; x < w; x++, move++, line++)
      if (*line != transparent)
	*move = *line;
  }
}
