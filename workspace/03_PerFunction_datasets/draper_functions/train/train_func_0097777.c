windfall_benefit(const struct city *src,
                               const struct city *dest,
                               const struct caravan_parameter *param) {
  if (!param->consider_windfall || !can_cities_trade(src, dest)) {
    return 0;
  }
  else {
    int bonus = get_caravan_enter_city_trade_bonus(src, dest);
    bool can_establish = can_establish_trade_route(src, dest);


    if (!can_establish) {
      bonus += 2;
      bonus /= 3;
    }


    bonus *= 2;
    return bonus;
  }
}
