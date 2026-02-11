update_dumb_city(struct player *pplayer, struct city *pcity)
{
  bv_imprs improvements;
  struct tile *pcenter = city_tile(pcity);
  struct vision_site *pdcity = map_get_player_city(pcenter, pplayer);


  bool occupied = (unit_list_size(pcenter->units) > 0);
  bool walls = city_got_citywalls(pcity);
  bool happy = city_happy(pcity);
  bool unhappy = city_unhappy(pcity);

  BV_CLR_ALL(improvements);
  improvement_iterate(pimprove) {
    if (is_improvement_visible(pimprove)
     && city_has_building(pcity, pimprove)) {
      BV_SET(improvements, improvement_index(pimprove));
    }
  } improvement_iterate_end;

  if (NULL == pdcity) {
    pdcity = vision_site_new_from_city(pcity);
    change_playertile_site(map_get_player_tile(pcenter, pplayer), pdcity);
  } else if (pdcity->location != pcenter) {
    log_error("Trying to update bad city (wrong location) "
              "at %i,%i for player %s",
              TILE_XY(pcity->tile), player_name(pplayer));
    pdcity->location = pcenter;
  } else if (pdcity->identity != pcity->id) {
    log_error("Trying to update old city (wrong identity) "
              "at %i,%i for player %s",
              TILE_XY(city_tile(pcity)), player_name(pplayer));
    pdcity->identity = pcity->id;
  } else if (pdcity->occupied == occupied
	  && pdcity->walls == walls
	  && pdcity->happy == happy
	  && pdcity->unhappy == unhappy
	  && BV_ARE_EQUAL(pdcity->improvements, improvements)
          && vision_site_size_get(pdcity) == city_size_get(pcity)
	  && vision_site_owner(pdcity) == city_owner(pcity)
	  && 0 == strcmp(pdcity->name, city_name(pcity))) {
    return FALSE;
  }

  vision_site_update_from_city(pdcity, pcity);
  pdcity->occupied = occupied;
  pdcity->walls = walls;
  pdcity->happy = happy;
  pdcity->unhappy = unhappy;
  pdcity->improvements = improvements;

  return TRUE;
}
