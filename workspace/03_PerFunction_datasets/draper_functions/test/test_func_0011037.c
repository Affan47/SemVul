ai_choose_help_wonder(struct city *pcity,
				  struct adv_choice *choice,
                                  struct adv_data *ai)
{
  struct player *pplayer = city_owner(pcity);
  Continent_id continent = tile_continent(pcity->tile);
  struct ai_city *city_data = def_ai_city_data(pcity);


  int caravans = 0;

  struct unit_type *unit_type;
  struct city *wonder_city = game_city_by_number(ai->wonder_city);

  if (num_role_units(F_HELP_WONDER) == 0) {

    return;
  }

  if (pcity == wonder_city
      || wonder_city == NULL
      || city_data->distance_to_wonder_city <= 0
      || VUT_UTYPE == wonder_city->production.kind
      || !is_wonder(wonder_city->production.value.building)) {


    return;
  }


  unit_list_iterate(pplayer->units, punit) {
    if (unit_has_type_flag(punit, F_HELP_WONDER)
        && tile_continent(unit_tile(punit)) == continent)
      caravans++;
  } unit_list_iterate_end;


  city_list_iterate(pplayer->cities, acity) {
    if (VUT_UTYPE == acity->production.kind
        && utype_has_flag(acity->production.value.utype, F_HELP_WONDER)
        && tile_continent(acity->tile) == continent) {
      caravans++;
    }
  } city_list_iterate_end;

  unit_type = best_role_unit(pcity, F_HELP_WONDER);

  if (!unit_type) {


    unit_type = get_role_unit(F_HELP_WONDER, 0);
  }


  if (build_points_left(wonder_city)
      > utype_build_shield_cost(unit_type) * caravans) {
    struct impr_type *wonder = wonder_city->production.value.building;
    int want = wonder_city->server.adv->building_want[improvement_index(wonder)];
    int dist = city_data->distance_to_wonder_city /
               unit_type->move_rate;

    fc_assert_ret(VUT_IMPROVEMENT == wonder_city->production.kind);

    want /= MAX(dist, 1);
    CITY_LOG(LOG_DEBUG, pcity, "want %s to help wonder in %s with %d",
             utype_rule_name(unit_type),
             city_name(wonder_city),
             want);
    if (want > choice->want) {


      unit_type = ai_wants_role_unit(pplayer, pcity, F_HELP_WONDER, want);
      if (unit_type != NULL) {
        choice->want = want;
        choice->type = CT_CIVILIAN;
        choice->value.utype = unit_type;
      } else {
        CITY_LOG(LOG_DEBUG, pcity,
                 "would but could not build F_HELP_WONDER unit, bumped reqs");
      }
    }
  }
}
