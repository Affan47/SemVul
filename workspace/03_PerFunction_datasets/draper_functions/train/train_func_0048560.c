canvas_to_city_pos(int *city_x, int *city_y, int city_radius_sq,
                        int canvas_x, int canvas_y)
{
#ifdef DEBUG
  int orig_canvas_x = canvas_x, orig_canvas_y = canvas_y;
#endif
  const int width = get_citydlg_canvas_width();
  const int height = get_citydlg_canvas_height();


  canvas_x -= (width - tileset_tile_width(tileset)) / 2;
  canvas_y -= (height - tileset_tile_height(tileset)) / 2;

  if (tileset_is_isometric(tileset)) {
    const int W = tileset_tile_width(tileset), H = tileset_tile_height(tileset);


    canvas_x -= W / 2;


    *city_x = DIVIDE(canvas_x * H + canvas_y * W, W * H);
    *city_y = DIVIDE(canvas_y * W - canvas_x * H, W * H);
  } else {
    *city_x = DIVIDE(canvas_x, tileset_tile_width(tileset));
    *city_y = DIVIDE(canvas_y, tileset_tile_height(tileset));
  }


  *city_x += CITY_MAP_MAX_RADIUS;
  *city_y += CITY_MAP_MAX_RADIUS;

  log_debug("canvas_to_city_pos(pos=(%d,%d))=(%d,%d)@radius=%d",
            orig_canvas_x, orig_canvas_y, *city_x, *city_y, city_radius_sq);

  return is_valid_city_coords(city_radius_sq, *city_x, *city_y);
}
