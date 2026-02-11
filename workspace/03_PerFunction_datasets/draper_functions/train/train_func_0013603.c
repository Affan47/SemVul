append_city_buycost_string(const struct city *pcity,
                                       char *buffer, int buffer_len)
{
  if (!pcity || !buffer || buffer_len < 1) {
    return;
  }

  if (!draw_city_buycost || !city_can_buy(pcity)) {
    return;
  }

  cat_snprintf(buffer, buffer_len, "/%d",
               city_production_buy_gold_cost(pcity));
}
