player_info_level(struct player *plr,
					     struct player *receiver)
{
  if (S_S_RUNNING > server_state()) {
    return INFO_MINIMUM;
  }
  if (plr == receiver) {
    return INFO_FULL;
  }
  if (receiver && player_has_embassy(receiver, plr)) {
    return INFO_EMBASSY;
  }
  if (receiver && could_intel_with_player(receiver, plr)) {
    return INFO_MEETING;
  }
  return INFO_MINIMUM;
}
