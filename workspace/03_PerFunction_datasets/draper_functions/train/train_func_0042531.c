base_get_direction_for_step(const struct tile *start_tile,
				 const struct tile *end_tile,
				 enum direction8 *dir)
{
  adjc_dir_iterate(start_tile, test_tile, test_dir) {
    if (same_pos(end_tile, test_tile)) {
      *dir = test_dir;
      return TRUE;
    }
  } adjc_dir_iterate_end;

  return FALSE;
}
