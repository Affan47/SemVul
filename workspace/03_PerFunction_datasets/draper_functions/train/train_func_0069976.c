have_cities_trade_route(const struct city *pc1, const struct city *pc2)
{
  int i;

  for (i = 0; i < NUM_TRADE_ROUTES; i++) {
    if (pc1->trade[i] == pc2->id || pc2->trade[i] == pc1->id) {

      return TRUE;
    }
  }
  return FALSE;
}
