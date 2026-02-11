player_new(struct player_slot *pslot)
{
  struct player *pplayer;

  fc_assert_ret_val(player_slots_initialised(), NULL);

  if (NULL == pslot) {
    player_slots_iterate(aslot) {
      if (!player_slot_is_used(aslot)) {
        pslot = aslot;
        break;
      }
    } player_slots_iterate_end;

    fc_assert_ret_val(NULL != pslot, NULL);
  } else if (NULL != pslot->player) {
    return pslot->player;
  }


  log_debug("Create player for slot %d.", player_slot_index(pslot));
  pplayer = fc_calloc(1, sizeof(*pplayer));
  pplayer->slot = pslot;
  pslot->player = pplayer;

  pplayer->diplstates = fc_calloc(player_slot_count(),
                                  sizeof(*pplayer->diplstates));
  player_slots_iterate(pslot) {
    const struct player_diplstate **diplstate_slot
      = pplayer->diplstates + player_slot_index(pslot);
    *diplstate_slot = NULL;
  } player_slots_iterate_end;

  players_iterate(aplayer) {

    player_diplstate_new(pplayer, aplayer);

    if (aplayer != pplayer) {
      player_diplstate_new(aplayer, pplayer);
    }
  } players_iterate_end;


  player_defaults(pplayer);


  player_slots.used_slots++;

  return pplayer;
}
