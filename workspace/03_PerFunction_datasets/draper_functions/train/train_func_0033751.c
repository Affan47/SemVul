get_city_specialist_output_bonus(const struct city *pcity,
				     const struct specialist *pspecialist,
				     const struct output_type *poutput,
				     enum effect_type effect_type)
{
  fc_assert_ret_val(pcity != NULL, 0);
  fc_assert_ret_val(pspecialist != NULL, 0);
  fc_assert_ret_val(poutput != NULL, 0);
  return get_target_bonus_effects(NULL,
				  city_owner(pcity), pcity, NULL,
				  NULL, NULL, poutput, pspecialist,
				  effect_type);
}
