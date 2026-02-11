player_has_trade_route_with_city(struct player *pplayer,
                                             struct city *pcity)
{
  int i;

  for (i = 0; i < NUM_TRADE_ROUTES; i++) {
    struct city *other = game_city_by_number(pcity->trade[i]);
    if (other && city_owner(other) == pplayer) {
      return TRUE;
    }
  }
  return FALSE;
}
