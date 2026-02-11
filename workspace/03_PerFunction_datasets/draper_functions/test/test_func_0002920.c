get_virtual_defense_power(const struct unit_type *att_type,
			      const struct unit_type *def_type,
			      const struct player *def_player,
			      const struct tile *ptile,
			      bool fortified, int veteran)
{
  int defensepower = def_type->defense_strength;
  int db;
  const struct veteran_level *vlevel;

  fc_assert_ret_val(def_type != NULL, 0);

  if (!can_exist_at_tile(def_type, ptile)) {

    return 0;
  }

  vlevel = utype_veteran_level(def_type, veteran);
  fc_assert_ret_val(vlevel != NULL, 0);

  db = POWER_FACTOR;
  if (uclass_has_flag(utype_class(def_type), UCF_TERRAIN_DEFENSE)) {
    db += tile_terrain(ptile)->defense_bonus / (100 / POWER_FACTOR);
    if (tile_has_special(ptile, S_RIVER)) {
      db += (db * terrain_control.river_defense_bonus) / 100;
    }
  }
  defensepower *= db;
  defensepower *= vlevel->power_fact / 100;

  return defense_multiplication(att_type, def_type, def_player,
                                ptile, defensepower,
                                fortified);
}
