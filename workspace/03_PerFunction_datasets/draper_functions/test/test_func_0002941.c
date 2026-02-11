city_tile_xy_to_index(int city_map_x, int city_map_y,
                          int city_radius_sq)
{
  fc_assert_ret_val(city_radius_sq >= CITY_MAP_MIN_RADIUS_SQ, 0);
  fc_assert_ret_val(city_radius_sq <= CITY_MAP_MAX_RADIUS_SQ, 0);
  fc_assert_ret_val(is_valid_city_coords(city_radius_sq, city_map_x,
                                         city_map_y), 0);

  return city_map_xy[city_map_x][city_map_y];
}
