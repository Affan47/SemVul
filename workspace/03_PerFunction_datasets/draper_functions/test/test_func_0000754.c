remove_obsolete_buildings_city(struct city *pcity, bool refresh)
{
  struct player *pplayer = city_owner(pcity);
  bool sold = FALSE;

  city_built_iterate(pcity, pimprove) {
    if (improvement_obsolete(pplayer, pimprove)
     && can_city_sell_building(pcity, pimprove)) {
      do_sell_building(pplayer, pcity, pimprove);
      notify_player(pplayer, city_tile(pcity), E_IMP_SOLD, ftc_server,
                    _("%s is selling %s (obsolete) for %d."),
                    city_link(pcity),
                    improvement_name_translation(pimprove),
                    impr_sell_gold(pimprove));
      sold = TRUE;
    }
  } city_built_iterate_end;

  if (sold && refresh) {
    city_refresh(pcity);
    send_city_info(pplayer, pcity);
    send_player_info_c(pplayer, NULL);
  }
}
