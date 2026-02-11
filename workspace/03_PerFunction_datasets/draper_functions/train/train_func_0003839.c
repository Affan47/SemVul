sell_random_building(struct player *pplayer,
                                 struct cityimpr_list *imprs)
{
  struct cityimpr *pcityimpr;
  int r;

  fc_assert_ret_val(pplayer != NULL, FALSE);

  if (!imprs || cityimpr_list_size(imprs) == 0) {
    return FALSE;
  }

  r = fc_rand(cityimpr_list_size(imprs));
  pcityimpr = cityimpr_list_get(imprs, r);

  notify_player(pplayer, city_tile(pcityimpr->pcity), E_IMP_AUCTIONED,
                ftc_server,
                _("Can't afford to maintain %s in %s, building sold!"),
                improvement_name_translation(pcityimpr->pimprove),
                city_link(pcityimpr->pcity));
  log_debug("%s: sold building (%s)", player_name(pplayer),
            improvement_name_translation(pcityimpr->pimprove));

  do_sell_building(pplayer, pcityimpr->pcity, pcityimpr->pimprove);

  cityimpr_list_remove(imprs, pcityimpr);


  pplayer->economic.gold += city_improvement_upkeep(pcityimpr->pcity,
                                                    pcityimpr->pimprove);

  city_refresh_queue_add(pcityimpr->pcity);

  FC_FREE(pcityimpr);

  return TRUE;
}
