draw_trade_routes_for_city(const struct city *pcity_src)
{
  int i;
  const struct city *pcity_dest;

  if (!pcity_src) {
    return;
  }

  for (i = 0; i < NUM_TRADE_ROUTES; i++) {
    pcity_dest = game_city_by_number(pcity_src->trade[i]);
    if (!pcity_dest) {
      continue;
    }
    draw_trade_route_line(city_tile(pcity_src), city_tile(pcity_dest),
                          COLOR_MAPVIEW_TRADE_ROUTE_LINE);
  }
}
