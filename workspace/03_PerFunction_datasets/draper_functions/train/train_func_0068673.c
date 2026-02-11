create_military_base_pixbuf(const struct base_type *pbase)
{
  struct drawn_sprite sprs[80];
  int count, w, h, canvas_x, canvas_y;
  GdkPixbuf *pixbuf;
  struct canvas canvas;

  w = tileset_tile_width(tileset);
  h = tileset_tile_height(tileset);

  pixbuf = gdk_pixbuf_new(GDK_COLORSPACE_RGB, TRUE, 8, w, h);
  if (pixbuf == NULL) {
    return NULL;
  }
  gdk_pixbuf_fill(pixbuf, 0x00000000);

  canvas.type = CANVAS_PIXBUF;
  canvas.v.pixbuf = pixbuf;
  canvas_x = 0;
  canvas_y = 0;

  count = fill_basic_base_sprite_array(tileset, sprs, pbase);
  put_drawn_sprites(&canvas, canvas_x, canvas_y, count, sprs, FALSE);

  return pixbuf;
}
