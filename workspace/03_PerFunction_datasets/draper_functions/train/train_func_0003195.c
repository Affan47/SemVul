spy_poison(struct player *pplayer, struct unit *pdiplomat,
		struct city *pcity)
{
  struct player *cplayer;


  if (!pcity)
    return;
  cplayer = city_owner(pcity);
  if (!cplayer || !pplayers_at_war(pplayer, cplayer))
    return;

  log_debug("poison: unit: %d", pdiplomat->id);


  if (!unit_has_type_flag(pdiplomat, F_SPY))
    return;


  if (!diplomat_infiltrate_tile(pplayer, cplayer, pdiplomat,
                                pcity->tile)) {
    return;
  }

  log_debug("poison: infiltrated");


  if (city_size_get(pcity) < 2) {
    notify_player(pplayer, city_tile(pcity),
                  E_MY_DIPLOMAT_FAILED, ftc_server,
                  _("Your %s could not poison the water"
                    " supply in %s."),
                  unit_link(pdiplomat),
                  city_link(pcity));
    log_debug("poison: target city too small");
    return;
  }

  log_debug("poison: succeeded");


  city_reduce_size(pcity, 1, pplayer);


  notify_player(pplayer, city_tile(pcity), E_MY_DIPLOMAT_POISON, ftc_server,
                _("Your %s poisoned the water supply of %s."),
                unit_link(pdiplomat),
                city_link(pcity));
  notify_player(cplayer, city_tile(pcity),
                E_ENEMY_DIPLOMAT_POISON, ftc_server,
                _("%s is suspected of poisoning the water supply of %s."),
                player_name(pplayer),
                city_link(pcity));


  city_refresh (pcity);
  send_city_info(NULL, pcity);


  maybe_cause_incident(SPY_POISON, pplayer, cplayer,
                       city_tile(pcity), city_link(pcity));


  diplomat_escape(pplayer, pdiplomat, pcity);
}
