update_bulbs(struct player *plr, int bulbs, bool check_tech)
{
  struct player_research *research = player_research_get(plr);


  plr->bulbs_last_turn += bulbs;
  research->bulbs_researched += bulbs;


  if (game.info.tech_upkeep_style > 0 && research->bulbs_researched < 0
      && (research->techs_researched > 0 || research->future_tech > 0)) {
    if (research->future_tech > 0) {
      notify_player(plr, NULL, E_TECH_GAIN, ftc_server,
                    _("Insufficient science output. We lost Future Tech. %d."),
                    research->future_tech);
      log_debug("%s: tech loss (future tech %d)", player_name(plr),
                research->future_tech);
      research->future_tech--;
    } else {
      Tech_type_id tech = pick_random_tech_researched(plr);
      if (tech != A_NONE) {
        notify_player(plr, NULL, E_TECH_GAIN, ftc_server,
                      _("Insufficient science output. We lost %s."),
                      advance_name_for_player(plr, tech));
        log_debug("%s: tech loss (%s)", player_name(plr),
                  advance_name_for_player(plr, tech));
        player_tech_lost(plr, tech);
      }
    }
    player_research_update(plr);

    research->bulbs_researched = 0;
  }

  if (check_tech && research->researching != A_UNSET) {

    if (research->bulbs_researched - total_bulbs_required(plr) >= 0) {
      tech_researched(plr);

      if (research->researching != A_UNSET) {

        update_bulbs(plr, 0, TRUE);
        return TRUE;
      }
    }
  }

  return FALSE;
}
