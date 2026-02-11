ai_caravan_goto(struct player *pplayer,
                            struct unit *punit,
                            const struct city *pcity,
                            bool help_wonder)
{
  bool alive = TRUE;

  fc_assert_ret(NULL != pcity);


  if (!same_pos(pcity->tile, unit_tile(punit)) && punit->moves_left != 0) {
    log_base(LOG_CARAVAN, "%s %s[%d](%d,%d) going to %s in %s",
             nation_rule_name(nation_of_unit(punit)),
             unit_rule_name(punit),
             punit->id,
             TILE_XY(unit_tile(punit)),
             help_wonder ? "help a wonder" : "trade", city_name(pcity));
    alive = ai_unit_goto(punit, pcity->tile);
  }


  if (alive && same_pos(pcity->tile, unit_tile(punit))) {
    if (help_wonder) {


      log_base(LOG_CARAVAN, "%s %s[%d](%d,%d) helps build wonder in %s",
               nation_rule_name(nation_of_unit(punit)),
               unit_rule_name(punit),
               punit->id,
               TILE_XY(unit_tile(punit)),
               city_name(pcity));
      handle_unit_help_build_wonder(pplayer, punit->id);
    } else {
      log_base(LOG_CARAVAN, "%s %s[%d](%d,%d) creates trade route in %s",
               nation_rule_name(nation_of_unit(punit)),
               unit_rule_name(punit),
               punit->id,
               TILE_XY(unit_tile(punit)),
               city_name(pcity));
      handle_unit_establish_trade(pplayer, punit->id);
    }
  }
}
