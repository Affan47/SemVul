load_cursors(void)
{
  enum cursor_type cursor;
  XColor white, black;
  struct sprite *sprite;
  int hot_x, hot_y;

  white.pixel = get_color(tileset, COLOR_OVERVIEW_VIEWRECT)->color.pixel;
  black.pixel = get_color(tileset, COLOR_OVERVIEW_UNKNOWN)->color.pixel;
  XQueryColor(display, cmap, &white);
  XQueryColor(display, cmap, &black);

  for (cursor = 0; cursor < CURSOR_LAST; cursor++) {
    sprite = get_cursor_sprite(tileset, cursor, &hot_x, &hot_y, 0);


    cursors[cursor] = XCreatePixmapCursor(display,
					  sprite->mask, sprite->mask,
					  &white, &black, hot_x, hot_y);
  }
}
