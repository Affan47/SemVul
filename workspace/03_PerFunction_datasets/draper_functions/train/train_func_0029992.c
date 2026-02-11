get_prod_complete_string(struct city *pcity, int surplus)
{
  int stock, cost, turns;
  static char buffer[50];

  if (surplus <= 0) {
    fc_snprintf(buffer, sizeof(buffer), _("never"));
    return buffer;
  }

  if (city_production_has_flag(pcity, IF_GOLD)) {
    fc_strlcpy(buffer, improvement_name_translation
               (pcity->production.value.building), sizeof(buffer));
    return buffer;
  }
  stock = pcity->shield_stock + surplus;
  cost = city_production_build_shield_cost(pcity);

  if (stock >= cost) {
    turns = 1;
  } else if (surplus > 0) {
    turns = ((cost - stock - 1) / surplus) + 1 + 1;
  } else {
    if (stock < 0) {
      turns = -1;
    } else {
      turns = (stock / surplus);
    }
  }
  fc_snprintf(buffer, sizeof(buffer), PL_("%d turn", "%d turns", turns),
              turns);
  return buffer;
}
