assess_danger_unit(const struct city *pcity,
                                       struct pf_reverse_map *pcity_map,
                                       const struct unit *punit,
                                       int *move_time)
{
  struct pf_position pos;
  const struct unit_type *punittype = unit_type(punit);
  const struct tile *ptile = city_tile(pcity);
  const struct unit *ferry;
  unsigned int danger;
  int mod;

  *move_time = PF_IMPOSSIBLE_MC;

  if (utype_has_flag(punittype, F_PARATROOPERS)
      && 0 < punittype->paratroopers_range) {
    *move_time = (real_map_distance(ptile, unit_tile(punit))
                  / punittype->paratroopers_range);
  }

  if (pf_reverse_map_unit_position(pcity_map, punit, &pos)
      && (PF_IMPOSSIBLE_MC == *move_time
          || *move_time > pos.turn)) {
    *move_time = pos.turn;
  }

  if (unit_transported(punit)
      && (ferry = unit_transport_get(punit))
      && pf_reverse_map_unit_position(pcity_map, ferry, &pos)) {
    if ((PF_IMPOSSIBLE_MC == *move_time
         || *move_time > pos.turn)) {
      *move_time = pos.turn;
      if (!can_attack_from_non_native(punittype)) {
        (*move_time)++;
      }
    }
  }

  if (PF_IMPOSSIBLE_MC == *move_time) {
    return 0;
  }
  if (!is_native_tile(punittype, ptile)
      && !can_attack_non_native(punittype)) {
    return 0;
  }
  if (is_sailing_unit(punit) && !is_ocean_near_tile(ptile)) {
    return 0;
  }

  danger = adv_unit_att_rating(punit);
  mod = 100 + get_unittype_bonus(city_owner(pcity), ptile,
                                 punittype, EFT_DEFEND_BONUS);
  return danger * 100 / MAX(mod, 1);
}
