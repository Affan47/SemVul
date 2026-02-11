ai_set_defenders(struct player *pplayer)
{
  city_list_iterate(pplayer->cities, pcity) {


    int total_defense = 0;
    int total_attack = def_ai_city_data(pcity)->danger;
    bool emergency = FALSE;
    int count = 0;

    while (total_defense <= total_attack) {
      int best_want = 0;
      struct unit *best = NULL;

      unit_list_iterate(pcity->tile->units, punit) {
        struct unit_ai *unit_data = def_ai_unit_data(punit);

       if ((unit_data->task == AIUNIT_NONE || emergency)
           && unit_data->task != AIUNIT_DEFEND_HOME
           && unit_owner(punit) == pplayer) {
          int want = assess_defense_unit(pcity, punit, FALSE);

          if (want > best_want) {
            best_want = want;
            best = punit;
          }
        }
      } unit_list_iterate_end;
      if (best == NULL) {

        if (emergency) {
          CITY_LOG(LOG_DEBUG, pcity, "Not defended properly");
          break;
        }
        emergency = TRUE;
      } else {
        int loglevel = pcity->server.debug ? LOG_AI_TEST : LOG_DEBUG;

        total_defense += best_want;
        UNIT_LOG(loglevel, best, "Defending city");
        ai_unit_new_task(best, AIUNIT_DEFEND_HOME, pcity->tile);
        count++;
      }
    }
    CITY_LOG(LOG_DEBUG, pcity, "Evaluating defense: %d defense, %d incoming"
             ", %d defenders (out of %d)", total_defense, total_attack, count,
             unit_list_size(pcity->tile->units));
  } city_list_iterate_end;
}
