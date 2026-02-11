place_island(struct gen234_state *pstate)
{
  int i=0, xn, yn, nat_x, nat_y;
  struct tile *ptile;

  ptile = rand_map_pos();
  index_to_native_pos(&nat_x, &nat_y, tile_index(ptile));


  for (yn = pstate->n, xn = pstate->w;
       yn < pstate->s && xn < pstate->e;
       yn++, xn++) {
    struct tile *tile0 = native_pos_to_tile(xn, yn);
    struct tile *tile1 = native_pos_to_tile(xn + nat_x - pstate->w,
                                            yn + nat_y - pstate->n);

    if (!tile0 || !tile1) {
      return FALSE;
    }
    if (hmap(tile0) != 0 && is_near_land(tile1)) {
      return FALSE;
    }
  }

  for (yn = pstate->n; yn < pstate->s; yn++) {
    for (xn = pstate->w; xn < pstate->e; xn++) {
      struct tile *tile0 = native_pos_to_tile(xn, yn);
      struct tile *tile1 = native_pos_to_tile(xn + nat_x - pstate->w,
                                              yn + nat_y - pstate->n);

      if (!tile0 || !tile1) {
	return FALSE;
      }
      if (hmap(tile0) != 0 && is_near_land(tile1)) {
	return FALSE;
      }
    }
  }

  for (yn = pstate->n; yn < pstate->s; yn++) {
    for (xn = pstate->w; xn < pstate->e; xn++) {
      if (hmap(native_pos_to_tile(xn, yn)) != 0) {
        struct tile *tile1 = native_pos_to_tile(xn + nat_x - pstate->w,
                                                yn + nat_y - pstate->n);

	checkmass--;
	if (checkmass <= 0) {
          log_error("mapgen.c: mass doesn't sum up.");
	  return i != 0;
	}

        tile_set_terrain(tile1, T_UNKNOWN);
	map_unset_placed(tile1);

	tile_set_continent(tile1, pstate->isleindex);
        i++;
      }
    }
  }

  pstate->s += nat_y - pstate->n;
  pstate->e += nat_x - pstate->w;
  pstate->n = nat_y;
  pstate->w = nat_x;

  return i != 0;
}
