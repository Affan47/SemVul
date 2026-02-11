map_pos_to_tile(int map_x, int map_y)
{
  int nat_x, nat_y;

  if (!map.tiles) {
    return NULL;
  }


  MAP_TO_NATIVE_POS(&nat_x, &nat_y, map_x, map_y);
  return base_native_pos_to_tile(nat_x, nat_y);
}
