ai_choose_trade_route(struct city *pcity,
				  struct adv_choice *choice,
                                  struct adv_data *ai)
{
  struct player *pplayer = city_owner(pcity);
  struct unit_type *unit_type;
  int want;
  int income, bonus;
  int trade_routes;
  Continent_id continent = tile_continent(pcity->tile);
  bool dest_city_found = FALSE;

  if (city_list_size(pplayer->cities) < 5) {


    return;
  }

  if (num_role_units(F_TRADE_ROUTE) == 0) {

    return;
  }


  city_list_iterate(pplayer->cities, acity) {
    if (can_cities_trade(pcity, acity) && tile_continent(acity->tile) == continent) {
      dest_city_found = TRUE;
      break;
    }
  } city_list_iterate_end;

  if(!dest_city_found) {

    return;
  }

  unit_type = best_role_unit(pcity, F_TRADE_ROUTE);

  if (!unit_type) {


    unit_type = get_role_unit(F_TRADE_ROUTE, 0);
  }

  trade_routes = city_num_trade_routes(pcity);

  unit_list_iterate(pcity->units_supported, punit) {
    if (unit_has_type_flag(punit, F_TRADE_ROUTE)) {
      trade_routes++;
    }
  } unit_list_iterate_end;


  income = (10 + 10) * (1.75 * pcity->surplus[O_TRADE]) / 24 * 3;
  bonus = get_city_bonus(pcity, EFT_TRADE_REVENUE_BONUS);
  income = (float)income * pow(2.0, (double)bonus / 1000.0);

  want = income * ai->gold_priority + income * ai->science_priority;


  want /= 130;


  if (pplayer->economic.science < 50 && trade_routes < NUM_TRADE_ROUTES) {
    want *=
      (6 - pplayer->economic.science/10) * (6 - pplayer->economic.science/10);
  }

  if (trade_routes == 0) {

    want += 20;
  } else if (trade_routes < NUM_TRADE_ROUTES) {

    want += 5;
  }

  want -= utype_build_shield_cost(unit_type) * SHIELD_WEIGHTING / 150;

  CITY_LOG(LOG_DEBUG, pcity,
           "want for trade route unit is %d (expected initial income %d)",
           want, income);

  if (want > choice->want) {


    unit_type = ai_wants_role_unit(pplayer, pcity, F_TRADE_ROUTE, want);
    if (unit_type != NULL) {
      choice->want = want;
      choice->type = CT_CIVILIAN;
      choice->value.utype = unit_type;
    } else {
      CITY_LOG(LOG_DEBUG, pcity,
               "would but could not build trade route unit, bumped reqs");
    }
  }
}
