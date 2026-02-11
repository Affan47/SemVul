can_city_build_improvement_now(const struct city *pcity,
				    struct impr_type *pimprove)
{
  if (!can_city_build_improvement_direct(pcity, pimprove)) {
    return FALSE;
  }
  if (improvement_obsolete(city_owner(pcity), pimprove)) {
    return FALSE;
  }
  return TRUE;
}
