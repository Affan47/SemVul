invasion_funct(struct unit *punit, bool dest, int radius,
			   int which)
{
  struct tile *ptile;
  struct player *pplayer = unit_owner(punit);

  CHECK_UNIT(punit);

  if (dest) {
    ptile = punit->goto_tile;
  } else {
    ptile = unit_tile(punit);
  }

  square_iterate(ptile, radius, tile1) {
    struct city *pcity = tile_city(tile1);

    if (pcity
        && HOSTILE_PLAYER(pplayer, city_owner(pcity))
	&& (dest || !has_defense(pcity))) {
      int attacks;
      struct ai_city *city_data = def_ai_city_data(pcity);

      if (unit_has_type_flag(punit, F_ONEATTACK)) {
        attacks = 1;
      } else {
        attacks = unit_type(punit)->move_rate;
      }
      city_data->invasion.attack += attacks;
      if (which == INVASION_OCCUPY) {
        city_data->invasion.occupy++;
      }
    }
  } square_iterate_end;
}
