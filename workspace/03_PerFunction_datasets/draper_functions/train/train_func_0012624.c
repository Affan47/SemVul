link_mark_draw(const struct link_mark *pmark)
{
  int width = tileset_tile_width(tileset);
  int height = tileset_tile_height(tileset);
  int xd = width / 20, yd = height / 20;
  int xlen = width / 3, ylen = height / 3;
  int canvas_x, canvas_y, x0, x1, y0, y1;
  struct tile *ptile = link_mark_tile(pmark);
  struct color *pcolor = link_mark_color(pmark);

  if (!ptile || !tile_to_canvas_pos(&canvas_x, &canvas_y, ptile)) {
    return;
  }

  x0 = canvas_x + xd;
  x1 = canvas_x + width - xd;
  y0 = canvas_y + yd;
  y1 = canvas_y + height - yd;

  canvas_put_line(mapview.store, pcolor, LINE_TILE_FRAME, x0, y0, xlen, 0);
  canvas_put_line(mapview.store, pcolor, LINE_TILE_FRAME, x0, y0, 0, ylen);

  canvas_put_line(mapview.store, pcolor, LINE_TILE_FRAME, x1, y0, -xlen, 0);
  canvas_put_line(mapview.store, pcolor, LINE_TILE_FRAME, x1, y0, 0, ylen);

  canvas_put_line(mapview.store, pcolor, LINE_TILE_FRAME, x0, y1, xlen, 0);
  canvas_put_line(mapview.store, pcolor, LINE_TILE_FRAME, x0, y1, 0, -ylen);

  canvas_put_line(mapview.store, pcolor, LINE_TILE_FRAME, x1, y1, -xlen, 0);
  canvas_put_line(mapview.store, pcolor, LINE_TILE_FRAME, x1, y1, 0, -ylen);
}
