sg_load_players(struct loaddata *loading)
{

  sg_check_ret();

  if (game.info.is_new_game) {

    return;
  }

  players_iterate(pplayer) {
    sg_load_player_main(loading, pplayer);
    sg_load_player_cities(loading, pplayer);
    sg_load_player_units(loading, pplayer);
    sg_load_player_attributes(loading, pplayer);


    sg_check_ret();


    if (pplayer->ai_controlled) {
      log_normal(_("%s has been added as %s level AI-controlled player "
                   "(%s)."), player_name(pplayer),
                 ai_level_name(pplayer->ai_common.skill_level),
                 ai_name(pplayer->ai));
    } else {
      log_normal(_("%s has been added as human player."),
                 player_name(pplayer));
    }
  } players_iterate_end;


  players_iterate(pplayer) {

    player_research_update(pplayer);

    sg_load_player_units_transport(loading, pplayer);
  } players_iterate_end;


  players_iterate(pplayer) {
    if (pplayer->nation == NO_NATION_SELECTED) {
      player_set_nation(pplayer, pick_a_nation(NULL, FALSE, TRUE,
                                               NOT_A_BARBARIAN));

      log_sg(_("%s had invalid nation; changing to %s."),
             player_name(pplayer), nation_plural_for_player(pplayer));
    }
  } players_iterate_end;


  players_iterate_alive(plr) {
    players_iterate_alive(aplayer) {
      if (pplayers_allied(plr, aplayer)) {
        enum dipl_reason can_ally = pplayer_can_make_treaty(plr, aplayer,
                                                            DS_ALLIANCE);
        if (can_ally == DIPL_ALLIANCE_PROBLEM_US
            || can_ally == DIPL_ALLIANCE_PROBLEM_THEM) {
          log_sg("Illegal alliance structure detected: "
                 "%s alliance to %s reduced to peace treaty.",
                 nation_rule_name(nation_of_player(plr)),
                 nation_rule_name(nation_of_player(aplayer)));
          player_diplstate_get(plr, aplayer)->type = DS_PEACE;
          player_diplstate_get(aplayer, plr)->type = DS_PEACE;
        }
      }
    } players_iterate_alive_end;
  } players_iterate_alive_end;


  cities_iterate(pcity) {
    city_refresh_from_main_map(pcity, NULL);
  } cities_iterate_end;


  players_iterate(pplayer) {
    sg_load_player_vision(loading, pplayer);

    sg_check_ret();
  } players_iterate_end;


  players_iterate(pplayer) {
    BV_CLR_ALL(pplayer->gives_shared_vision);
    BV_CLR_ALL(pplayer->server.really_gives_vision);
  } players_iterate_end;

  players_iterate(pplayer) {
    int plr1 = player_index(pplayer);

    players_iterate(pplayer2) {
      int plr2 = player_index(pplayer2);
      if (secfile_lookup_bool_default(loading->file, FALSE,
              "player%d.diplstate%d.gives_shared_vision", plr1, plr2)) {
        give_shared_vision(pplayer, pplayer2);
      }
    } players_iterate_end;
  } players_iterate_end;

  initialize_globals();
  unit_ordering_apply();


  map_calculate_borders();


  players_iterate(pplayer) {
    unit_list_iterate(pplayer->units, punit) {
      if (!can_unit_continue_current_activity(punit)) {
        log_sg("Unit doing illegal activity in savegame!");
        punit->activity = ACTIVITY_IDLE;
      }
    } unit_list_iterate_end;
  } players_iterate_end;

  cities_iterate(pcity) {
    city_refresh(pcity);
    city_thaw_workers(pcity);
  } cities_iterate_end;
}
