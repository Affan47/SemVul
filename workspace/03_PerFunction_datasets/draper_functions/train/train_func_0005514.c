stack_risk(const struct tile *ptile,
                      struct adv_risk_cost *risk_cost,
                      const struct pf_parameter *param)
{
  double risk = 0;

  const double value = risk_cost->base_value
                       + stack_value(ptile, param->owner);
  const double p_killed = chance_killed_at(ptile, risk_cost, param);
  double danger = value * p_killed;


  risk += danger * risk_cost->fearfulness;


  if (risk_cost->enemy_zoc_cost != 0
      && (is_non_allied_city_tile(ptile, param->owner)
	  || !is_my_zoc(param->owner, ptile)
	  || is_non_allied_unit_tile(ptile, param->owner))) {

    risk += risk_cost->enemy_zoc_cost;
  }

  return risk;
}
