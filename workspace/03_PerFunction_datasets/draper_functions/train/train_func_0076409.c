find_nearest_safe_city(struct unit *punit)
{
  struct pf_parameter parameter;
  struct pf_map *pfm;
  struct player *pplayer = unit_owner(punit);
  struct city *pcity, *best_city = NULL;
  int best = FC_INFINITY, cur;

  pft_fill_unit_parameter(&parameter, punit);
  pfm = pf_map_new(&parameter);

  pf_map_move_costs_iterate(pfm, ptile, move_cost, TRUE) {
    if (move_cost > best) {

      break;
    }

    pcity = tile_city(ptile);
    if (NULL == pcity || !pplayers_allied(pplayer, city_owner(pcity))) {
      continue;
    }


    cur = move_cost;


    if (0 == get_unittype_bonus(unit_owner(punit), ptile, unit_type(punit),
                               EFT_HP_REGEN)) {


      cur *= 3;
    }

    if (cur < best) {
      best_city = pcity;
      best = cur;
    }
  } pf_map_move_costs_iterate_end;

  pf_map_destroy(pfm);
  return best_city;
}
