worklist_id_to_name(char buf[],
			 struct universal production,
			 struct city *pcity)
{
  if (VUT_UTYPE == production.kind)
    sprintf(buf, "%s (%d)",
	    utype_values_translation(production.value.utype),
	    utype_build_shield_cost(production.value.utype));
  else if (pcity)
    sprintf(buf, "%s (%d)",
	    city_improvement_name_translation(pcity, production.value.building),
	    impr_build_shield_cost(production.value.building));
  else
    sprintf(buf, "%s (%d)",
	    improvement_name_translation(production.value.building),
	    impr_build_shield_cost(production.value.building));
}
