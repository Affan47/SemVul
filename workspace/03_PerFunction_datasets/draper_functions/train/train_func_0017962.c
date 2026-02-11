adv_danger_at(struct unit *punit, struct tile *ptile)
{
  int a = 0, d, db;
  struct player *pplayer = unit_owner(punit);
  struct city *pcity = tile_city(ptile);
  enum danger_consideration dc = DANG_UNDECIDED;


  CALL_PLR_AI_FUNC(consider_tile_dangerous, unit_owner(punit), ptile, punit, &dc);
  if (dc == DANG_YES) {
    return TRUE;
  } else if (dc == DANG_NOT) {
    return FALSE;
  }

  if (pcity && pplayers_allied(city_owner(pcity), unit_owner(punit))
      && !is_non_allied_unit_tile(ptile, pplayer)) {

    return FALSE;
  }


  db = 10 + tile_terrain(ptile)->defense_bonus / 10;
  if (tile_has_special(ptile, S_RIVER)) {
    db += (db * terrain_control.river_defense_bonus) / 100;
  }
  d = adv_unit_def_rating_basic_sq(punit) * db;

  adjc_iterate(ptile, ptile1) {
    if (!map_is_known_and_seen(ptile1, unit_owner(punit), V_MAIN)) {

      continue;
    }
    unit_list_iterate(ptile1->units, enemy) {
      if (pplayers_at_war(unit_owner(enemy), unit_owner(punit))
          && can_unit_attack_unit_at_tile(enemy, punit, ptile)
          && can_unit_attack_units_at_tile(enemy, ptile)) {
        a += adv_unit_att_rating(enemy);
        if ((a * a * 10) >= d) {

          return TRUE;
        }
      }
    } unit_list_iterate_end;
  } adjc_iterate_end;

  return FALSE;
}
