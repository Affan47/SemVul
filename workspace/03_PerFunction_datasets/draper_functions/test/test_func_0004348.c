ai_unit_bodyguard_move(struct unit *bodyguard, struct tile *ptile)
{
  struct unit *punit;
  struct player *pplayer;

  fc_assert_ret(bodyguard != NULL);
  pplayer = unit_owner(bodyguard);
  fc_assert_ret(pplayer != NULL);
  punit = aiguard_charge_unit(bodyguard);
  fc_assert_ret(punit != NULL);

  CHECK_GUARD(bodyguard);
  CHECK_CHARGE_UNIT(punit);

  if (!is_tiles_adjacent(ptile, unit_tile(bodyguard))) {
    return;
  }

  if (bodyguard->moves_left <= 0) {

    BODYGUARD_LOG(LOG_DEBUG, bodyguard, "was left behind by charge");
    return;
  }

  unit_activity_handling(bodyguard, ACTIVITY_IDLE);
  (void) ai_unit_move(bodyguard, ptile);
}
