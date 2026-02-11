ai_military_attack_barbarian(struct player *pplayer,
					 struct unit *punit)
{
  struct city *pc;
  bool only_continent = TRUE;

  if (unit_transported(punit)) {


    only_continent = FALSE;
  }

  if ((pc = find_closest_city(unit_tile(punit), NULL, pplayer, FALSE,
                              only_continent, FALSE, FALSE, TRUE, NULL))) {
    if (can_unit_exist_at_tile(punit, unit_tile(punit))) {
      UNIT_LOG(LOG_DEBUG, punit, "Barbarian heading to conquer %s",
               city_name(pc));
      (void) ai_gothere(pplayer, punit, pc->tile);
    } else {
      struct unit *ferry = NULL;

      if (unit_transported(punit)) {
        ferry = unit_transport_get(punit);


        if (!is_boat_free(ferry, punit, 0)) {

          ferry = NULL;
        }
      } else {

        unit_list_iterate(unit_tile(punit)->units, aunit) {
          if (is_boat_free(aunit, punit, 1)
              && unit_transport_load(punit, aunit, FALSE)) {
            ferry = aunit;
            break;
          }
        } unit_list_iterate_end;
      }

      if (ferry) {
	UNIT_LOG(LOG_DEBUG, punit, "Barbarian sailing to conquer %s",
		 city_name(pc));
	(void)aiferry_goto_amphibious(ferry, punit, pc->tile);
      } else {


        UNIT_LOG(LOG_DEBUG, punit, "unable to find barbarian ferry");
      }
    }
  } else {
    UNIT_LOG(LOG_DEBUG, punit, "Barbarian find no target city");
  }
}
