city_reduce_workers(struct city *pcity, citizens change)
{
  struct tile *pcenter = city_tile(pcity);
  int want = change;

  fc_assert_ret_val(0 < change, 0);

  city_tile_iterate_skip_free_worked(city_map_radius_sq_get(pcity), pcenter,
                                     ptile, _index, _x, _y) {
    if (0 < want && tile_worked(ptile) == pcity) {
      city_map_update_empty(pcity, ptile);
      want--;
    }
  } city_tile_iterate_skip_free_worked_end;

  return change - want;
}
