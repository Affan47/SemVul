get_modified_firepower(const struct unit *attacker,
			    const struct unit *defender,
			    int *att_fp, int *def_fp)
{
  struct city *pcity = tile_city(unit_tile(defender));

  *att_fp = unit_type(attacker)->firepower;
  *def_fp = unit_type(defender)->firepower;


  if (unit_has_type_flag(attacker, F_CITYBUSTER) && pcity) {
    *att_fp *= 2;
  }


  if (unit_has_type_flag(attacker, F_BADWALLATTACKER)
      && get_unittype_bonus(unit_owner(defender), unit_tile(defender),
                            unit_type(attacker), EFT_DEFEND_BONUS) > 0) {
    *att_fp = 1;
  }


  if (unit_has_type_flag(defender, F_BADCITYDEFENDER)
      && tile_city(unit_tile(defender))) {
    *att_fp *= 2;
    *def_fp = 1;
  }


  if (unit_has_type_flag(defender, F_HELICOPTER)
      && unit_has_type_flag(attacker, F_FIGHTER)) {
    *def_fp = 1;
  }


  if (is_sailing_unit(attacker)
      && !is_ocean_tile(unit_tile(defender))
      && is_ground_unit(defender)) {
    *att_fp = 1;
    *def_fp = 1;
  }
}
