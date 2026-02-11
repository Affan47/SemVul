city_tile_output(const struct city *pcity, const struct tile *ptile,
		     bool is_celebrating, Output_type_id otype)
{
  int prod;
  struct terrain *pterrain = tile_terrain(ptile);

  fc_assert_ret_val(otype >= 0 && otype < O_LAST, 0);

  if (T_UNKNOWN == pterrain) {


    return 0;
  }

  prod = pterrain->output[otype];
  if (tile_resource_is_valid(ptile)) {
    prod += tile_resource(ptile)->output[otype];
  }

  switch (otype) {
  case O_SHIELD:
    if (tile_has_special(ptile, S_MINE)) {
      prod += pterrain->mining_shield_incr;
    }
    break;
  case O_FOOD:

    if (tile_has_special(ptile, S_IRRIGATION)
        || (NULL != pcity
            && is_city_center(pcity, ptile)
            && pterrain == pterrain->irrigation_result
            && !tile_has_special(ptile, S_MINE)
            && terrain_control.may_irrigate)) {
      prod += pterrain->irrigation_food_incr;
    }
    break;
  case O_TRADE:
    if (tile_has_special(ptile, S_RIVER) && !is_ocean_tile(ptile)) {
      prod += terrain_control.river_trade_incr;
    }
    if (tile_has_special(ptile, S_ROAD)) {
      prod += pterrain->road_trade_incr;
    }
    break;
  case O_GOLD:
  case O_SCIENCE:
  case O_LUXURY:
  case O_LAST:
    break;
  }

  if (tile_has_special(ptile, S_RAILROAD)) {
    prod += (prod * terrain_control.rail_tile_bonus[otype]) / 100;
  }

  if (pcity) {
    const struct output_type *output = &output_types[otype];

    prod += get_city_tile_output_bonus(pcity, ptile, output,
				       EFT_OUTPUT_ADD_TILE);
    if (prod > 0) {
      int penalty_limit = get_city_tile_output_bonus(pcity, ptile, output,
                                                   EFT_OUTPUT_PENALTY_TILE);

      if (is_celebrating) {
        prod += get_city_tile_output_bonus(pcity, ptile, output,
                                           EFT_OUTPUT_INC_TILE_CELEBRATE);
        penalty_limit = 0;
      }
      prod += get_city_tile_output_bonus(pcity, ptile, output,
                                         EFT_OUTPUT_INC_TILE);
      prod += (prod
               * get_city_tile_output_bonus(pcity, ptile, output,
                                            EFT_OUTPUT_PER_TILE))
              / 100;
      if (!is_celebrating && penalty_limit > 0 && prod > penalty_limit) {
        prod--;
      }
    }
  }

  if (tile_has_special(ptile, S_POLLUTION)) {
    prod -= (prod * terrain_control.pollution_tile_penalty[otype]) / 100;
  }

  if (tile_has_special(ptile, S_FALLOUT)) {
    prod -= (prod * terrain_control.fallout_tile_penalty[otype]) / 100;
  }

  if (NULL != pcity && is_city_center(pcity, ptile)) {
    prod = MAX(prod, game.info.min_city_center_output[otype]);
  }

  return prod;
}
