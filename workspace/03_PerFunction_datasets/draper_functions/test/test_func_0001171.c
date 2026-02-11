escp2_density(const stp_vars_t *v)
{
  if (stp_check_float_parameter(v, "escp2_density", STP_PARAMETER_ACTIVE))
    return stp_get_float_parameter(v, "escp2_density");
  else
    {
      const res_t *res1 = stp_escp2_find_resolution(v);
      if (res1->v &&
	  stp_check_float_parameter(res1->v, "escp2_density", STP_PARAMETER_ACTIVE))
	return stp_get_float_parameter(res1->v, "escp2_density");
    }
  return 0;
}
