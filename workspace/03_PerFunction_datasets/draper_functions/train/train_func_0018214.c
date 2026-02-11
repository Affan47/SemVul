team_slot_rule_name(const struct team_slot *tslot)
{
  fc_assert_ret_val(team_slots_initialised(), NULL);
  fc_assert_ret_val(NULL != tslot, NULL);

  if (NULL == tslot->rule_name) {

    struct team_slot *changeable
      = team_slot_by_number(team_slot_index(tslot));
    team_slot_create_default_name(changeable);
    return changeable->rule_name;
  }

  return tslot->rule_name;
}
