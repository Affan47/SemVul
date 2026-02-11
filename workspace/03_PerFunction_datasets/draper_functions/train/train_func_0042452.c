advance_has_flag(Tech_type_id tech, enum tech_flag_id flag)
{
  fc_assert_ret_val(tech_flag_id_is_valid(flag), FALSE);
  return BV_ISSET(advance_by_number(tech)->flags, flag);
}
