ai_diplomacy_get(const struct player *plr1,
                                      const struct player *plr2)
{
  fc_assert_ret_val(plr1 != NULL, NULL);
  fc_assert_ret_val(plr2 != NULL, NULL);

  const struct ai_dip_intel **player_intel_slot
    = def_ai_player_data(plr1)->diplomacy.player_intel_slots
      + player_index(plr2);

  fc_assert_ret_val(player_intel_slot != NULL, NULL);

  return (struct ai_dip_intel *) *player_intel_slot;
}
