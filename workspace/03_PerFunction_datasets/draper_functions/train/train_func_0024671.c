igter_move_unit(const struct tile *ptile,
                           enum direction8 dir,
                           const struct tile *ptile1,
                           const struct pf_parameter *param)
{
  int move_cost;

  if (!is_native_tile_to_class(param->uclass, ptile1)) {
    if (unit_class_transporter_capacity(ptile1, param->owner,
                                        param->uclass) > 0) {
      move_cost = MOVE_COST_ROAD;
    } else {
      move_cost = PF_IMPOSSIBLE_MC;
    }
  } else if (!is_native_tile_to_class(param->uclass, ptile)) {
    if (!BV_ISSET(param->unit_flags, F_MARINES)
        && (is_non_allied_unit_tile(ptile1, param->owner)
            || is_non_allied_city_tile(ptile1, param->owner))) {
      move_cost = PF_IMPOSSIBLE_MC;
    } else {
      move_cost = MOVE_COST_ROAD;
    }
  } else if (uclass_has_flag(param->uclass, UCF_TERRAIN_SPEED)) {
    move_cost = (map_move_cost(param->owner, ptile, ptile1) != 0
                 ? MOVE_COST_ROAD : 0);
  } else {
    move_cost = SINGLE_MOVE;
  }
  return move_cost;
}
