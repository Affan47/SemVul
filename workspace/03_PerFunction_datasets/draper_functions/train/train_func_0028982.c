find_a_good_partisan_spot(struct tile *pcenter,
                                      struct player *powner,
                                      struct unit_type *u_type,
                                      int sq_radius,
                                      struct tile **dst_tile)
{
  int bestvalue = 0;


  circle_iterate(pcenter, sq_radius, ptile) {
    int value;

    if (is_ocean_tile(ptile)
        || !is_native_tile(u_type, ptile)) {
      continue;
    }

    if (NULL != tile_city(ptile)) {
      continue;
    }

    if (0 < unit_list_size(ptile->units)) {
      continue;
    }


    value = get_virtual_defense_power(NULL, u_type, powner,
				      ptile, FALSE, 0);
    value *= 10;

    if (tile_continent(ptile) != tile_continent(pcenter)) {
      value /= 2;
    }

    value -= fc_rand(value/3);

    if (value > bestvalue) {
      *dst_tile = ptile;
      bestvalue = value;
    }
  } circle_iterate_end;

  return bestvalue > 0;
}
