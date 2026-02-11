end_phase(void)
{
  log_debug("Endphase");


  phase_players_iterate(pplayer) {


    lsend_packet_end_phase(pplayer->connections);
  } phase_players_iterate_end;

  phase_players_iterate(pplayer) {
    if (A_UNSET == player_research_get(pplayer)->researching) {
      Tech_type_id next_tech =
          player_research_step(pplayer,
                               player_research_get(pplayer)->tech_goal);

      if (A_UNSET != next_tech) {
        choose_tech(pplayer, next_tech);
      } else {
        choose_random_tech(pplayer);
      }


      update_bulbs(pplayer, 0, FALSE);
    }
  } phase_players_iterate_end;


  send_city_suppression(TRUE);


  players_iterate(pplayer) {
    unit_list_iterate(pplayer->units, punit) {
      CALL_PLR_AI_FUNC(unit_turn_end, pplayer, punit);
    } unit_list_iterate_end;
  } players_iterate_end;
  phase_players_iterate(pplayer) {
    auto_settlers_player(pplayer);
    if (pplayer->ai_controlled) {
      CALL_PLR_AI_FUNC(last_activities, pplayer, pplayer);
    }
  } phase_players_iterate_end;


  phase_players_iterate(pplayer) {
    player_research_get(pplayer)->got_tech = FALSE;
  } phase_players_iterate_end;

  phase_players_iterate(pplayer) {
    do_tech_parasite_effect(pplayer);
    player_restore_units(pplayer);
    update_city_activities(pplayer);
    player_research_get(pplayer)->researching_saved = A_UNKNOWN;


    update_bulbs(pplayer, -player_research_get(pplayer)->tech_upkeep, TRUE);
    flush_packets();
  } phase_players_iterate_end;

  kill_dying_players();


  send_city_suppression(FALSE);

  phase_players_iterate(pplayer) {
    send_player_cities(pplayer);
  } phase_players_iterate_end;
  flush_packets();

  do_reveal_effects();
  do_have_embassies_effect();

  phase_players_iterate(pplayer) {
    CALL_PLR_AI_FUNC(phase_finished, pplayer, pplayer);


    adv_data_phase_done(pplayer);
  } phase_players_iterate_end;
}
