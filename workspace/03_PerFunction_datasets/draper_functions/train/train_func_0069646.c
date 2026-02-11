calc_unit_ordering(void)
{
  int j;

  players_iterate(pplayer) {

    unit_list_iterate(pplayer->units, punit) {
      punit->server.ord_city = 0;
    } unit_list_iterate_end;
    city_list_iterate(pplayer->cities, pcity) {
      j = 0;
      unit_list_iterate(pcity->units_supported, punit) {
	punit->server.ord_city = j++;
      } unit_list_iterate_end;
    } city_list_iterate_end;
  } players_iterate_end;

  whole_map_iterate(ptile) {
    j = 0;
    unit_list_iterate(ptile->units, punit) {
      punit->server.ord_map = j++;
    } unit_list_iterate_end;
  } whole_map_iterate_end;
}
