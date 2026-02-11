get_city_growth_string(struct city *pcity, int surplus)
{
  int stock, cost, turns;
  static char buffer[50];

  if (surplus == 0) {
    fc_snprintf(buffer, sizeof(buffer), _("never"));
    return buffer;
  }

  stock = pcity->food_stock;
  cost = city_granary_size(city_size_get(pcity));

  stock += surplus;

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
